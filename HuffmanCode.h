//
// Created by Adrian Hwang on 2024-08-31.
//

#ifndef HUFFMANCODE_H
#define HUFFMANCODE_H
class Node
{
public:
    friend class HuffmanCode;
private:
    char data='\0';
    int freq=0;
    Node* left=nullptr;
    Node* right=nullptr;
public:
    Node(char data_in,int freq_in):data(data_in),freq(freq_in){}
    Node()=default;
    int get_freq() const
    {
        return freq;
    }
};

class CommpareSecond
{
    public:
        bool operator()(const Node* node1,const Node* node2) const
        {
            return node1->get_freq() > node2->get_freq();  //greater for min_heap
        }
};

class HuffmanCode
{
private:
    std::string str;
    std::unordered_map<char,int> freq_map;
    //pq's arg (data,base container,compare)
        //std::pair has a default comparison operator (operator<) which compares the first elements of the pairs first, and if they are equal, it then compares the second elements. This is how std::less (which uses operator<) works with pairs:

    //the following two priority queue can work in standart C++ but not supported by CLion
    // std::priority_queue<std::pair<char,int>,std::vector<std::pair<char,int>>,std::function<bool(const std::pair<char, int>&, const std::pair<char, int>&)>> pq(
    //     [](const std::pair<char,int>& pair1,const std::pair<char,int>& pair2)->bool
    //     {
    //         return pair1.second>pair2.second;
    //     }
    // );

    // auto compare=[](const std::pair<char, int>& pair1, const std::pair<char, int>& pair2) -> bool {
    //     return pair1.second > pair2.second;
    // };
    // std::priority_queue<std::pair<char, int>, std::vector<std::pair<char, int>>, std::function<bool(const std::pair<char, int>&, const std::pair<char, int>&)>> pq(compare);
    std::priority_queue<Node*, std::vector<Node*>, CommpareSecond> pq;

    std::unordered_map<char,std::string> char_code_map;
    Node* root;
public:
    HuffmanCode(const std::string& input_str):str(input_str)
    {
        //count the frequency of each char
        __count_freq();
        //transfer to a priority queue
        __map2pq();
        //build the HuffmanTree
        __build_HuffmanTree();
        //traverse HuffmanTree
        // __traverse(root);
        //encrypt the string
        __encrypt();
    }
private:
    void __traverse(Node* cur_node)
    {
        if(cur_node==nullptr) return;
        std::cout<<"("<<cur_node->data<<","<<cur_node->freq<<")"<<std::endl;
        __traverse(cur_node->left);
        __traverse(cur_node->right);
    }

    void __count_freq()
    {
        std::cout<<"----------------Start counting frequency-----------------"<<std::endl;
        for(auto c:str)
        {
            freq_map[c]++;  //don't have to initialize
        }
        std::cout<<"----------------counting frequency is done----------------"<<std::endl;
    }
    void __map2pq()
    {
        std::cout<<"----------------Start converting unordered_map to priority queue----------------"<<std::endl;
        for(auto& p:freq_map)
        {
            Node* node=new Node(p.first,p.second);
            pq.push(node);
        }

        //check the priority queue, don't uncomment this block on the fly. It will cause empty pq.
        // while(!pq.empty())
        // {
        //     Node* p=pq.top();
        //     pq.pop();
        //     std::cout<<"("<<p->data<<","<<p->freq<<")"<<std::endl;
        // }
        std::cout<<"----------------converting unordered_map to priority is done----------------"<<std::endl;
    }

    void __build_HuffmanTree()
    {
        std::cout<<"----------------Start building huffmantree----------------"<<std::endl;
        while(!pq.empty())
        {
            //if there is only one node left, it is the root
            if(pq.size()==1)
            {
                root=pq.top();
                pq.pop();
                break;
            }
            //if there are more than one node left
            //get two nodes with the smallest frequency
            Node* node1=pq.top();
            pq.pop();
            Node* node2=pq.top();
            pq.pop();
            //create a new node with the sum of the two nodes' frequency
            //created nodes have no char data, but its freq is the sum of the two children
            Node* parent=new Node('\0',node1->freq+node2->freq);
            //set the two nodes as the children of the parent
            parent->left=node1;
            parent->right=node2;
            //push the parent node back to the pq
            pq.push(parent);
        }
        std::cout<<"----------------building huffmantree is done----------------"<<std::endl;
    }

    void __encrypt()
    {
        std::cout<<"----------------Start encrypting each char to binary string-----------------"<<std::endl;
        //traverse the tree to get the binary code of each char
        __traverseAndCode(root,"");
        std::cout<<"----------------encrypting each char to binary string is done-----------------"<<std::endl;
    }

    //becaue each traverse stage has a different code, so we need to pass the code to the next stage
    void __traverseAndCode(Node* node,std::string code)
    {
        if(node==nullptr) return;
        //if the node is a leaf node, store the code
        if(node->left==nullptr && node->right==nullptr)
        {
            char_code_map[node->data]=code;
            std::cout<<node->data<<":"<<code<<std::endl;
            return;
        }
        //traverse the left child
        __traverseAndCode(node->left,code+"0");
        //traverse the right child
        __traverseAndCode(node->right,code+"1");
    }
};

#endif //HUFFMANCODE_H
