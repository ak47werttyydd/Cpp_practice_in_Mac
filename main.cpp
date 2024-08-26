#include <iostream>
#include "TrieTree.h"
#include "StringComp_KMP.h"

void test_TrieTree()
{
    TrieTree tr;
    tr.insert("apple");
    tr.insert("app");
    tr.insert("banana");
    tr.insert("band");
    tr.insert("bandit");
    tr.insert("bandage");
    tr.insert("bandana");
    // TrieNode* cur_node=tr.search_pattern_lastNode("ban");
    // tr.traverse_curNode(cur_node);
    tr.print_relative_pattern("ban");
    // tr.print_levelwise_from_curNode(cur_node);
    std::cout<<"--------------------"<<std::endl;
    // tr.print_levelwise_from_curNode(tr.get_root());
}

void test_StringComp_KMP()
{
    StringComp_KMP kmp("abxabcabxabx","abx");
}



int main()
{
    std::cout << "Hello, World!" << std::endl;
    test_StringComp_KMP();
    return 0;
}
