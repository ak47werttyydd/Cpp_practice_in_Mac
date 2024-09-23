//
// Created by Adrian Hwang on 2024-09-15.
//

#ifndef CANBECONNECTED_H
#define CANBECONNECTED_H
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>
#include <unordered_map>

class Friend
{
public:
    std::vector<Friend*> friends;
    static std::unordered_map<Friend*,bool> visited;

    Friend(std::string email)
    {
        this->email = email;
    }

    void addFriendship(Friend* target)
    {
        friends.push_back(target);
        target->friends.push_back(this);
    }

    //dfs
    bool canBeConnected(Friend* target)
    {
        if(this==target)
            return true;
        //dfs
        for(auto f:friends)
        {
            //have visited
            if(visited[f])
                continue;

            visited[f]=true;
            if(f==target) //found
                return true;
            else //not found, continue to search
            {
                if(f->canBeConnected(target))
                    return true;
            }
        }
        return false;
    }

private:
    std::string email;
};
#endif //CANBECONNECTED_H
