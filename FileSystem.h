//
// Created by Adrian Hwang on 2024-08-30.
//

//Create a file system, it has a path and a value, combing the path and the value.
    //if the path doesn't exist, create it

/* structure
//class
//a filesys
        //check th path
        //make the path_value_pair
//two kinds of structure
    //path is a string:    /a/b/c/d/e.   wave
    //split the path by "/"
    //extract the prefix from the root "/"
    //loop to check the existence of the prefix and store in hashmap
        hashmap m;
        m["/"]=exist? 1:  0;
        m["/a"]=exist? 1:  0;
        m["/a/b"]=exist? 1:  0;
        after we scaning the string we have a filled hashmap
        for loop to scanning the hashmap, once we get a 0, the path doesn't exist

    //or store in a trie whose nodes has a hashmap to store the subsequent path
            //trie is good to deal with the common prefix

    abcdefg
    abc.  (prefix)
    abcde.  (prefix)

//struct
//path_value_pair
        //path
        //value
*/

#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <string>
#include <iostream>
#include <unordered_map>
#include <sstream>

template<typename T = int>
struct PathValue{
    template<typename> friend class Filesys;
    std::string path;
    T value;
    PathValue(std::string path_in,T value_in = 0):path(path_in),value(value_in){}
    PathValue():path("/"),value(0){}
    ~PathValue()=default;
};


class TrieNode_str{
public:
    template <typename> friend class Filesys;
private:
    std::string name="/";
    bool isEnd=false;
    TrieNode_str* parentNode=nullptr;
    std::unordered_map<std::string,TrieNode_str*> subNode;
public:
    TrieNode_str(std::string name_in):name(name_in){}
    TrieNode_str()=default;
    ~TrieNode_str()=default;
};

template<typename T = int>  //
class Filesys{
private:
    //store the path and value input
    std::string path="/";  //default path is root
    T value;  //default value is 0 by ctor
    //using trie tree to store the path
    TrieNode_str* root=new TrieNode_str();  //keep in mind to delete in the deconstructor
    PathValue<T> pv;
public:
    //constructor
    Filesys(std::string path_in, T value_in = 0):path{path_in},value{value_in}
    {
        //store the path in the trie tree, then combine the path and value
        pv =__insert_pathInTrie();
    }

    //deconstructor
    //don't need to implement a destructor (~TrieNode_str) in the TrieNode_str class because all linked TrieNode_str are deleted recursively.
    ~Filesys()
    {
        __recursively_delete_node(root);
    }
    //recursively delete the node
    void __recursively_delete_node(TrieNode_str* node)
    {
        //termination
        if(node==nullptr) return;
        //post-order traversal
        for(auto it=node->subNode.begin();it!=node->subNode.end();it++)
        {
            __recursively_delete_node(it->second);
        }
        delete node;
    }

    //split the path by "/" and return a vector of strings
    std::vector<std::string> __split_path(){
        char delimiter='/';
        std::vector<std::string> names;  //store all names in the path
        std::string name;  //store the name get by getline()
        std::istringstream ss(path);
        while(std::getline(ss,name,delimiter)){
            names.push_back(name);
        }
        return names;
    }

    //insert_pathInTrie
    PathValue<T> __insert_pathInTrie()
    {
        std::vector<std::string> names=__split_path();
        TrieNode_str* cur_node=root;
        for(std::string name : names)
        {
            if(cur_node->subNode.find(name)==cur_node->subNode.end()) //no this name
            {
                //create the path
                // __create_dir(name);

                //build a new node for this name, and insert
                TrieNode_str* newNode=new TrieNode_str(name);  //keep in mind to delete in the deconstructor
                cur_node->subNode[name]=newNode;
            }
            //move to next node, and set the parent node
            TrieNode_str* parent_node=cur_node; //keep track of the parent node
            cur_node=cur_node->subNode[name];
            cur_node->parentNode=parent_node;
        }
        cur_node->isEnd=true;
        return PathValue<T>(path,value);
    }


    // //does the path exist?
    // bool __exist(){
    //         //whether the path exist
    //         if(no exist)return false;
    //         else true;
    //     }
    //
    // //read the path
    // bool read(){
    //     //whether the path exist?
    //     if(!__exist()){//exist
    //         __create_path();
    //     }
    //     PathValue<T> pvp=new PathValue(path,value);
    // }

    //create the path
    // bool __create_pdir();
};

#endif //FILESYSTEM_H
