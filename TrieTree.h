//
// Created by Adrian Hwang on 2024-08-21.
//

#ifndef TIERTREE_H
#define TIERTREE_H
#include <string>
#include <iostream>
#include <queue>
#include <vector>

class TrieNode
{
public:
    friend class TrieTree;
private:
    char data='\0';
    bool isEnd=false;
    TrieNode* parentNode=nullptr;
    TrieNode* subNode[26]={nullptr}; // if subnodes are "a", "z", subNode[0] and subNode[25] have corresponding TrieNode

public:
    TrieNode(const char& input_data):data(input_data){}
    TrieNode()=default;
};

class TrieTree
{
private:
    TrieNode* root=new TrieNode();
public:
    TrieTree()=default;
    void insert(std::string string_input)
    {
        TrieNode* cur_node=root;
        for(char char_in_str: string_input)
        {
            int char_index=static_cast<int>(char_in_str-'a');
            if(cur_node->subNode[char_index]==nullptr){ //no this subnode, create
                TrieNode* newNode=new TrieNode(char_in_str);
                cur_node->subNode[char_index]=newNode;
            }
            TrieNode* parent_node=cur_node;
            parent_node->isEnd=false;
            cur_node=cur_node->subNode[char_index]; //move to next node
            cur_node->parentNode=parent_node;
        }
        cur_node->isEnd=true;
    }
    TrieNode* search_pattern_lastNode(const std::string& pattern)
    {
        TrieNode* cur_node=root;
        for(char char_in_str: pattern)
        {
            int char_index=static_cast<int>(char_in_str-'a');
            if(cur_node->subNode[char_index]==nullptr){ //no this subnode
                std::cout<<"No match found"<<std::endl;
                return nullptr;
            }
            cur_node=cur_node->subNode[char_index]; //move to next node
        }
        std::cout<<"Match found"<<std::endl;
        std::cout<<"char is "<<cur_node->data<<std::endl;
        return cur_node;
    }

    void traverse_curNode(TrieNode* cur_node, std::vector<TrieNode*>& leaf_nodes)
    {
        if(cur_node==nullptr)  //if cur_node is nullptr
        {
            return;
        }else if(cur_node->isEnd){ //if cur_node is leaf node
            leaf_nodes.push_back(cur_node);
        }
        else{ //if cur_node is not leaf node
            for(int i=0;i<=25;i++)  //iterate subnodes
            {
                TrieNode* subNode=cur_node->subNode[i];
                if(subNode==nullptr)
                {
                    continue;
                }else
                {
                    traverse_curNode(subNode, leaf_nodes);
                }
            }
        }
    }

    void print_relative_pattern(const std::string& pattern)
    {
        TrieNode* cur_node=search_pattern_lastNode(pattern);
        std::vector<TrieNode*> leaf_nodes;
        traverse_curNode(cur_node, leaf_nodes); //get all leaf nodes
        for(TrieNode* leaf_node: leaf_nodes)
        {
            std::string relative_pattern;
            TrieNode* cur_node=leaf_node;
            while(cur_node->parentNode!=nullptr)
            {
                relative_pattern=cur_node->data+relative_pattern;
                cur_node=cur_node->parentNode;
            }
            std::cout<<relative_pattern<<std::endl;
        }
    }

    void print_levelwise_from_curNode(TrieNode* cur_node)
    {
        if(cur_node==nullptr)
        {
            return;
        }else{
            std::queue<TrieNode*> q;  //store nodes to be visited
            q.push(cur_node);
            int level=0;
            while(!q.empty()) //traverse through all level
            {
                size_t size_cur_level=q.size();
                std::cout<<"Level "<<level<<": ";
                for(int j=0;j<size_cur_level;j++){ //traverse through all nodes in the same level
                    TrieNode* cur_node=q.front();
                    std::cout<<cur_node->data<<" ";
                    q.pop();
                    //push all subnodes of cur_node to queue
                    for(int i=0;i<=25;i++)
                    {
                        TrieNode* subNode=cur_node->subNode[i];
                        if(subNode!=nullptr)  //if subnode exists
                        {
                            q.push(subNode);
                        }
                    }
                }
                std::cout<<std::endl;
                level++; //finish a level
            }
        }
    }

    TrieNode* get_root()
    {
        return root;
    }
};

#endif //TIERTREE_H
