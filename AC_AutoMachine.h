//
// Created by Adrian Hwang on 2024-08-26.
//

#ifndef AC_AUTOMACHINE_H
#define AC_AUTOMACHINE_H
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

class AC_Node
{
public:
    friend class AC_Tree;
    typedef AC_Node* NodePtr;
    typedef AC_Node self;
private:
    char data='\0';  //default data of the node, root's data is '\0', each node store a char
    bool isEnd=false; //if leafnode, isEnd=true
    int depth=0; //if leafnode, record the depth of a node, the depth of root is 0
    NodePtr failNode=nullptr; //failNode is the longest suffix of the current pattern that is also the longest prefix of another pattern
    NodePtr parentNode=nullptr;
    NodePtr subNode[26]={nullptr}; // if subnodes are "a", "z", subNode[0] and subNode[25] have corresponding TrieNode

public:
    AC_Node(const char& input_data):data(input_data){}
    AC_Node()=default;
};

class AC_Tree
{
public:
    typedef AC_Node* NodePtr;
    typedef AC_Node Node;
    typedef AC_Tree self;
private:
    //tree structre stores all patterns
    NodePtr root=new Node(); //root node with default setting
    std::vector<NodePtr> leaves;  //store all leaf nodes
    std::string main_str="";
    std::vector<std::pair<int,int>> found_idx_len; //record the index of the first char of the found pattern in the main_str and the length of the pattern
public:
    AC_Tree(std::string main_str_input,std::vector<std::string> patterns_input):main_str(main_str_input)
    {
        //insert all patterns into the tree
        for(std::string pattern: patterns_input)
        {
            insert(pattern);
        }
        //set leaves
        traverseCurNode_and_getLeaves_fromRoot();
        //set failNode
        set_failNode();
        //print the tree level-wise
        print_levelwise_from_curNode(root);
        //search_patterns
        search_patterns();
    }
    AC_Tree()=default;
    //insert a pattern string into the tree
    void insert(std::string string_input)
    {
        int cur_depth=0;
        NodePtr cur_node=root;
        for(char char_in_str: string_input)
        {
            //get the index of the subnode
            int char_index=static_cast<int>(char_in_str-'a');
            //no this subnode, create and link to subNode
            if(cur_node->subNode[char_index]==nullptr){
                NodePtr newNode=new Node(char_in_str);
                cur_node->subNode[char_index]=newNode;
            }
            NodePtr parent_node=cur_node;
            //isEnd is the end of a pattern instead of a leaf node, so don't set it to true
            // parent_node->isEnd=false;
            cur_node=cur_node->subNode[char_index]; //move to next node
            cur_node->depth=++cur_depth; //update the depth of the node
            cur_node->parentNode=parent_node;
        }
        //no more characters in the string, cur_node is a leaf node
        cur_node->isEnd=true;
    }

    // TrieNode* search_pattern_lastNode(const std::string& pattern)
    // {
    //     TrieNode* cur_node=root;
    //     for(char char_in_str: pattern)
    //     {
    //         int char_index=static_cast<int>(char_in_str-'a');
    //         if(cur_node->subNode[char_index]==nullptr){ //no this subnode
    //             std::cout<<"No match found"<<std::endl;
    //             return nullptr;
    //         }
    //         cur_node=cur_node->subNode[char_index]; //move to next node
    //     }
    //     std::cout<<"Match found"<<std::endl;
    //     std::cout<<"char is "<<cur_node->data<<std::endl;
    //     return cur_node;
    // }

    void traverseCurNode_and_getLeaves_fromRoot()
    {
        std::cout<<"--------starting traverseCurNode_and_getLeaves-----------"<<std::endl;
        _traverseCurNode_and_getLeaves(root);
        std::cout<<"--------traverseCurNode_and_getLeaves is done-----------"<<std::endl;
    }

    //leaf_nodes store all leaf nodes of the tree
    void _traverseCurNode_and_getLeaves(NodePtr cur_node)
    {
        //termination condition
        if(cur_node==nullptr)  //if cur_node is nullptr
        {
            return;
        }else if(cur_node->isEnd){ //if cur_node is leaf node
            leaves.push_back(cur_node);
        }
        else{ //if cur_node is not leaf node
            for(int i=0;i<=25;i++)  //iterate subnodes
            {
                NodePtr subNode=cur_node->subNode[i];
                if(subNode==nullptr)  //some subnodes may not exist
                {
                    continue;
                }else
                { //if subnode[i] exists, traverse it
                    _traverseCurNode_and_getLeaves(subNode);
                }
            }
        }
    }

    // void print_relative_pattern(const std::string& pattern)
    // {
    //     TrieNode* cur_node=search_pattern_lastNode(pattern);
    //     std::vector<TrieNode*> leaf_nodes;
    //     traverse_curNode(cur_node, leaf_nodes); //get all leaf nodes
    //     for(TrieNode* leaf_node: leaf_nodes)
    //     {
    //         std::string relative_pattern;
    //         TrieNode* cur_node=leaf_node;
    //         while(cur_node->parentNode!=nullptr)
    //         {
    //             relative_pattern=cur_node->data+relative_pattern;
    //             cur_node=cur_node->parentNode;
    //         }
    //         std::cout<<relative_pattern<<std::endl;
    //     }
    // }
    //
    void print_levelwise_from_curNode(NodePtr cur_node)
    {
        std::cout<<"--------starting print_levelwise_from_curNode-----------"<<std::endl;
        if(cur_node==nullptr)  //if cur_node is nullptr
        {
            return;
        }else{  //if cur_node is not nullptr
            std::queue<NodePtr> queue;  //store nodes to be visited
            queue.push(cur_node);
            //get the level of the cur_node
            int level=cur_node->depth;
            // while(cur_node!=root)
            // {
            //     cur_node=cur_node->parentNode;
            //     level++;
            // }
            while(!queue.empty()) //traverse through the entire tree
            {
                size_t size_cur_level=queue.size(); //# of nodes in the current level
                std::cout<<"Level "<<level<<": ";
                for(int j=0;j<size_cur_level;j++){ //traverse through all nodes in the same level
                    cur_node=queue.front();
                    std::cout<<"(data: "<<cur_node->data<<", curNode: "<<cur_node<<", failNode: "<< cur_node->failNode<<", depth: "<<cur_node->depth<<", isEnd: "<<cur_node->isEnd<<") ";
                    queue.pop();
                    //push all subnodes of cur_node to queue
                    for(int i=0;i<=25;i++)
                    {
                        NodePtr subNode=cur_node->subNode[i];
                        if(subNode!=nullptr)  //if subnode exists
                        {
                            queue.push(subNode);
                        }
                    }
                }
                std::cout<<std::endl;
                level++; //finish a level
            }
        }
        std::cout<<"--------print_levelwise_from_curNode is done-----------"<<std::endl;
    }


    void print_leaves()
    {
        for(NodePtr leaf: leaves)
        {
            std::cout<<leaf->data<<std::endl;
        }
    }

    void set_failNode()
    {
        std::cout<<"-----------start set_failNode------------------"<<std::endl;
        std::queue<NodePtr> queue;
        queue.push(root);
        root->failNode=nullptr;
        while(!queue.empty())
        {
            NodePtr p=queue.front();  //get the first node in the queue
            queue.pop();
            for(int i=0;i<26;i++)  //iterate all subnodes of p
            {
                NodePtr pc=p->subNode[i];  //get the subnode[i] of p
                if(pc==nullptr)continue;
                //set pc's failNode
                if(p==root)
                {
                    pc->failNode=root;  //find pc's failNode
                }else
                {
                    NodePtr q=p->failNode;  //q may be nullptr
                    while(q!=nullptr)
                    {
                        NodePtr qc=q->subNode[i];
                        if(qc!=nullptr)  //q has subNode[i] (i.e. qc's char = pc's char)
                        {
                            pc->failNode=qc;  //find pc's failNode
                            break;
                        }else //q does not have subNode[i], move q to q's failNode
                        {
                            q=q->failNode;
                        }
                    }
                    if(q==nullptr)  //don't find any failNode for pc
                    {
                        pc->failNode=root;
                    }
                }
                queue.push(pc);  //push pc to queue after setting the failNode of pc.
            }
        }
        std::cout<<"-----------set_failNode is done------------------"<<std::endl;
    }

    //search patterns
    void search_patterns()
    {
        std::cout<<"------------start search_patterns---------------"<<std::endl;
        NodePtr p=root;
        for(int i=0;i<main_str.size();i++)
        {
            int idx=static_cast<int>(main_str[i]-'a');
            while(p->subNode[idx]==nullptr && p!=root) //p's children don't match main_str[i]
            {
                p=p->failNode;
            }
            //p has subNode[idx]  (find a new mathcing char)
            //or p is root (no matching char)
            p=p->subNode[idx]; //move to the next node
            if(p==nullptr) //no matching char
            {
                p=root;
            }
            NodePtr tmp=p;
            while(tmp!=root) //iterate all failnodes(substrings or suffix) of the current pattern
            {
                if(tmp->isEnd) //find a pattern becuase reaching to its end(leaf node)
                {
                    int idx_found=i-tmp->depth+1;
                    int len_found=tmp->depth;
                    std::cout<<"Pattern found at index: "<<idx_found<<", length: "<<len_found<<std::endl;
                    std::pair<int,int> idx_len=std::make_pair(idx_found,len_found);
                    found_idx_len.push_back(idx_len);
                }
                tmp=tmp->failNode;
            }
        }
        std::cout<<"------------search_patterns is done---------------"<<std::endl;
    }

    void print_found_patterns()
    {
        for(auto idx_len: found_idx_len)
        {
            std::cout<<"Pattern found at index: "<<idx_len.first<<", length: "<<idx_len.second<<std::endl;
        }
    }

    NodePtr get_root()
    {
        return root;
    }
};



#endif //AC_AUTOMACHINE_H
