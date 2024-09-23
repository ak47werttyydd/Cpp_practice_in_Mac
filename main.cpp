#include <iostream>
#include "TrieTree.h"
#include "StringComp_KMP.h"
#include "AC_AutoMachine.h"
#include "FileSystem.h"
#include "HuffmanCode.h"
#include "MeetingRoom.h"
#include "Inversion.h"
#include "2D_ClosestPair.h"
#include "MinimalNumberOfPackages.h"
#include "FlipShift.h"
#include "SlidingWindows.h"
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
void test_FileSystem()
{
    Filesys<long> fs("/home/",100);
}
void test_HaffmanCode()
{
    HuffmanCode hc("this is an example of a huffman tree");
}
void test_MeetingRoom()
{
    MeetingRoom mr({{1,2},{2,5},{6,8},{8,11},{3,9},{9,12},{4,7},{9,13}});
}
void test_heap()
{
    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <functional> // for std::greater
    std::vector<int> minHeap = {5, 10, 20, 15, 30};

    // Convert the vector into a min-heap
    std::make_heap(minHeap.begin(), minHeap.end(), std::greater<int>());

    std::cout << "Original min-heap: ";
    for (int n : minHeap) std::cout << n << " ";
    std::cout << std::endl;

    // Modify an element in the heap
    minHeap[1] = 3; // change the value at index 1 to 3

    // Restore the heap property after modification
    std::push_heap(minHeap.begin(), minHeap.begin() + 2, std::greater<int>()); // Adjust the element at index 1

    std::cout << "Min-heap after modification: ";
    for (int n : minHeap) std::cout << n << " ";
    std::cout << std::endl;
}
void test_inversion()
{
    int arr[6]={2,4,3,1,5,6};
    int size=sizeof(arr)/sizeof(arr[0]);
    int inversion_count=count_inversion(arr,size);
    std::cout<<"inversion count: "<<inversion_count<<std::endl;
}
void test_2D_ClosestPair(){
    std::vector<Point> P = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    std::cout << "The smallest distance is " << closestPair(P) << std::endl;
}
void test_MinimalNumberOfPackages()
{
    cout<<MinimalNumberOfPackages(10,2,1)<<endl;
    cout<<MinimalNumberOfPackages(16,2,10)<<endl;
    cout<<MinimalNumberOfPackages(21,2,10)<<endl;
    cout<<MinimalNumberOfPackages(9,2,10)<<endl;
}
void test_FlipShift()
{
    int a = 7;  // 0000 0111
    int b = 17; // 0001 0001

    int* result = flipShift(a, b);
    delete[] result; //avoid memory leaks after use.
}
void test_SlidingWindows()
{
    //brute force
    int arr[6]={2,4,3,1,5,6};
    int return_size;
    //brute force
    int* output_arr=rolling_maximum_of_array_bruteforce(arr,6,3,return_size); //true output should be 4,4,5,6
    //output_size=4=6-3+1 check
    //print the output array
    if(output_arr)
    {
        for(int i=0;i<return_size;i++)
        {
            cout<<"arr["<<i<<"] is"<<output_arr[i]<<endl;
        }
        delete[] output_arr;
    }

    //heap
    int* output_arr_heap=rolling_maximum_of_array_heap(arr,6,3,return_size); //true output should be 4,4,5,6
    if(output_arr_heap)
    {
        for(int i=0;i<return_size;i++)
        {
            cout<<"arr["<<i<<"] is"<<output_arr_heap[i]<<endl;
        }
        delete[] output_arr;
    }
}

int main()
{
    std::cout << "Hello, World!" << std::endl;
    // test_2D_ClosestPair();
    // test_MinimalNumberOfPackages();
    // test_FlipShift();
    test_SlidingWindows();
    return 0;



}
