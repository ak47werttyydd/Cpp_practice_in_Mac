//
// Created by Adrian Hwang on 2024-12-28.
//

#ifndef ASYNPUBSUB_H
#define ASYNPUBSUB_H
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <iostream>
#include <future>
#include <chrono>
#include <thread>

class Message
{
private:
    std::string topic;
    std::string message;
    // std::vector<std::string> subscribers;
public:
    Message(const std::string& arg_topic,const std::string& arg_msg): topic(arg_topic),message(arg_msg) {}
    std::string getMsg() const { return message; }
    void setMsg(const std::string& arg_msg) { message = arg_msg; } //deep copy
    std::string getTopic() const { return topic; }
    void setTopic(const std::string& arg_topic) { topic = arg_topic; }
};

//store messages from Publisher to MessageBroker
class InputChannel
{
protected:
    std::unordered_map<std::string, std::shared_ptr<Message>> messages;
public:
    void addMessage(const std::shared_ptr<Message>& arg_msg) { messages[arg_msg->getTopic()] = arg_msg; } //the Message object is not copied; instead, the shared pointer is copied, and the reference count is incremented.
    void removeMessage(const std::string& topic) { messages.erase(topic); }
    std::shared_ptr<Message> getMessage(const std::string& topic)
    {
        auto it = messages.find(topic);
        if (it == messages.end()) return nullptr;
        return it->second;
    }
};

//store messages from MessageBroker to Subscriber
class OutputChannel: public InputChannel
{
private:
    std::string subscriber_name;
public:
    explicit OutputChannel(const std::string& arg_subscriber_name):subscriber_name(arg_subscriber_name){};
};

class MessageBroker
{
private:
    InputChannel* inputChannel;
    std::unordered_map<std::string,std::vector<std::string>> subscriptions; //key: topic, value: vector of subscriber names
    std::unordered_map<std::string,OutputChannel*> outputChannels; //key: subscriber's name, value: OutputChannel pointer
public:
    MessageBroker(){inputChannel=new InputChannel();}
    //destruct inputChannel and outputChannels
    ~MessageBroker() {
        delete inputChannel;
        for (auto& pair : outputChannels) {
            delete pair.second;
        }
    }
    [[nodiscard]] InputChannel* getInputChannel() const { return inputChannel; }
    [[nodiscard]] OutputChannel* getOutputChannel(const std::string& arg_subscriber_name)
    {
        auto it = outputChannels.find(arg_subscriber_name);
        if ( it == outputChannels.end() ) return nullptr;
        return it->second;
    }
    std::unordered_map<std::string,OutputChannel*> getOutputChannels() { return outputChannels; }
    void addSubscriber(const std::string& arg_subscriber_name) { outputChannels[arg_subscriber_name] = new OutputChannel(arg_subscriber_name); }
    void removeSubscriber(const std::string& arg_subscriber_name)
    {
        delete outputChannels[arg_subscriber_name]; //delete the OutputChannel object
        outputChannels.erase(arg_subscriber_name); //remove the key-value pair from the map
    }
    void subscribe(const std::string& arg_topic, const std::string& arg_subscriber_name)
    {
        subscriptions[arg_topic].push_back(arg_subscriber_name);
    }
    void unsubscribe(const std::string& arg_topic, const std::string& arg_subscriber_name)
    {
        auto it = subscriptions.find(arg_topic);
        if (it == subscriptions.end()) return;
        std::vector<std::string>& subscribers = it->second; //if no &, subscribers is a deep copy
        subscribers.erase(
                        std::remove(subscribers.begin(),subscribers.end(), arg_subscriber_name),
                        subscribers.end()
                         );
    }
    //send messages from inputChannel to outputChannels based on subscriptions
    //remove the message from inputChannel after sending
    //remove subscriptions which have been sent, and keep the rest which have not been sent
    void msgBroadcast()
    {
        //iterate through all topics in subscriptions
        for(auto it=subscriptions.begin(); it!=subscriptions.end(); )
        {
            const std::string& topic = it->first; //key is const
            const std::shared_ptr<Message>& msg = inputChannel->getMessage(topic); //return an rvalue of type std::shared_ptr<Message>. Only const lvalue references can bind to rvalues.
            if (!msg)
            {
                ++it;
            }else
            {
                std::vector<std::string>& subscribers = it->second;
                //iterate through all subscribers of the topic, and transfer the message to each subscriber's OutputChannel
                for(auto it2=subscribers.begin(); it2!=subscribers.end(); ++it2)
                {
                    std::string& subscriber_name=*it2;
                    outputChannels[subscriber_name]->addMessage(msg);
                }
                //remove the message from the InputChannel
                inputChannel->removeMessage(topic);
                //remove current topic from subscriptions and update the iterator
                it=subscriptions.erase(it);
            }
        }
    }
};

class Publisher
{
private:
    MessageBroker *messageBroker;
public:
    explicit Publisher(MessageBroker* arg_messageBroker):messageBroker(arg_messageBroker){}
    void publish(const std::shared_ptr<Message>& arg_msg) const { messageBroker->getInputChannel()->addMessage(arg_msg); }
    void publish(const std::string& arg_topic, const std::string& arg_msg) const { messageBroker->getInputChannel()->addMessage(std::make_shared<Message>(arg_topic,arg_msg)); }
    //asynchronously wait and publish message
    [[nodiscard]] std::future<void> async_publish(std::future<std::shared_ptr<Message>> msg_future) const {
        return std::async(
            std::launch::async,
            [this, msg_future = std::move(msg_future)]() mutable
            {
                std::shared_ptr<Message> new_msg = msg_future.get();
                this->publish(new_msg);
            }
        );
    }
};

class Subscriber
{
private:
    MessageBroker *messageBroker;
    std::string subscriber_name;
public:
    [[nodiscard]] std::string getName() const { return subscriber_name; }
    Subscriber(MessageBroker* arg_messageBroker, const std::string& arg_subscriber_name):messageBroker(arg_messageBroker),subscriber_name(arg_subscriber_name)
    {
        messageBroker->addSubscriber(subscriber_name);
    }
    void subscribeMsg(const std::string& arg_topic) const { messageBroker->subscribe(arg_topic,subscriber_name); }
    void unsubscribeMsg(const std::string& arg_topic) const { messageBroker->unsubscribe(arg_topic,subscriber_name); }
    [[nodiscard]] std::shared_ptr<Message> get_Message_delete(const std::string& arg_topic) const
    {
        OutputChannel* outputChannel = messageBroker->getOutputChannel(subscriber_name);
        if (outputChannel == nullptr) return nullptr;
        std::shared_ptr<Message> tmp_msg=outputChannel->getMessage(arg_topic);
        if (tmp_msg == nullptr) return nullptr;
        //there are corresponding outputchannel and message
        //remove the message from the OutputChannel
        outputChannel->removeMessage(arg_topic);
        return tmp_msg;
    }
    [[nodiscard]] std::shared_ptr<Message> action(const std::string& action_name,const int& seconds, const std::string& topic, const std::string& message) const
    {
        std::cout << action_name <<" of "<< subscriber_name <<" started for " << seconds << " seconds.\n";
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
        std::cout << "Action of "<< subscriber_name <<" completed.\n";
        return std::make_shared<Message>(topic,message);
    }
};

// int main()
// {
//     //initialize the message broker
//     MessageBroker messageBroker;
//     //initialize the publisher
//     Publisher publisher1(&messageBroker);
//     //initialize 2 subscribers, and they are automatically added to the messagebroker. And their corresponding outputChannels are created.
//     Subscriber subscriber2(&messageBroker,"subscriber2");
//     Subscriber subscriber3(&messageBroker,"subscriber3");
//     Subscriber subscriber4(&messageBroker,"subscriber4");
//     //publisher publishes a mmessage "msg_1" to the inputChannel of the messageBroker
//     publisher1.publish("msg_1","Please take actions");
//     //subscriber1 and subscriber2 subscribes to the topic "msg_1"
//     subscriber2.subscribeMsg("msg_1");
//     subscriber3.subscribeMsg("msg_1");
//     subscriber4.subscribeMsg("msg_2");
//     subscriber4.subscribeMsg("msg_3");
//
//     //messageBroker sends the message to the outputChannels of subscriber1 and subscriber2
//     messageBroker.msgBroadcast();
//     //subscriber1 and subscriber2 asynchronously receives the message and take actions. So action2 and action3 are executed in parallel.
//     std::future<std::shared_ptr<Message>> result2= //future msg_2
//         std::async(
//                 std::launch::async,
//                 [&subscriber2]() //action is a member function, so bind is to the object by lambda function
//                 {
//                     //subscriber2 receives the message
//                     if(subscriber2.get_Message_delete("msg_1"))
//                     {
//                         //execute action_2
//                         return subscriber2.action("action_2", 5, "msg_2", "action_2 completed");
//                     }
//                     return std::make_shared<Message>("msg_2_error","subscriber2 does not receive msg_1");
//                 }
//         );
//     std::future<std::shared_ptr<Message>> result3= //future msg_3
//         std::async(
//                 std::launch::async,
//                 [&subscriber3]()
//                 {
//                     //subscriber3 receives the message
//                     if(subscriber3.get_Message_delete("msg_1"))
//                     {
//                         //execute action_3
//                         return subscriber3.action("action_3", 10, "msg_3", "action_3 completed");
//                     }
//                     return std::make_shared<Message>("msg_3_error","subscriber3 does not receive msg_1");
//                 } //action is a member function, so bind is to the object by lambda function
//         );
//
//     //asyn publish msg_2 and msg_3, so they are not blocked by each other
//     std::future<void> future2 = publisher1.async_publish(std::move(result2));
//     std::future<void> future3 = publisher1.async_publish(std::move(result3));
//
//     //wait msg_2 and msg_3 to be published
//     future2.wait();
//     future3.wait();
//
//     //messageBroker sends msg_2 and msg_3 to the outputChannels of subscriber4
//     messageBroker.msgBroadcast();
//
//     //subscriber4 receives msg_2 and msg_3 and then takes actions to produce msg_4
//     std::shared_ptr<Message> msg_4;
//     if(subscriber4.get_Message_delete("msg_2") && subscriber4.get_Message_delete("msg_3"))
//     {
//         //execute action_4
//         msg_4=subscriber4.action("action_4", 2, "msg_4", "action_4 completed");
//         std::cout<<msg_4->getMsg()<<std::endl;
//     }
//
//     return 0;
// }

#endif //ASYNPUBSUB_H
