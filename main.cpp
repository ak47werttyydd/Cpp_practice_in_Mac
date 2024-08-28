#include <iostream>
#include "TrieTree.h"
#include "StringComp_KMP.h"
#include "AC_AutoMachine.h"
using namespace std;

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
    StringComp_KMP kmp2("cbdasdfwqwcbcadaff4qjjcbca","cbca");
}
void test_AC_AutoMachine()
{

    vector<string> patterns={"hersa","he","she","his","hers","a"};
    string main_str="uashersa";
    AC_Tree ac(main_str,patterns);
    ac.print_found_patterns();
    /*
    Pattern found at index: 1, length: 1
    Pattern found at index: 2, length: 3
    Pattern found at index: 3, length: 4
    Pattern found at index: 3, length: 5
    Pattern found at index: 7, length: 1*/
}

int main()
{
    std::cout << "Hello, World!" << std::endl;
    test_AC_AutoMachine();
    return 0;
}
