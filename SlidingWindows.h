//
// Created by Adrian Hwang on 2024-09-18.
//

#ifndef MICROSOFTINTERVIEW1_H
#define MICROSOFTINTERVIEW1_H
#include <iostream>
#include <vector>
#include <algorithm>
//fun rolling maxium of interger array
// random number
// windows size

// what is rolling maxium?
    //     is it
    // [2,1,3,5,4]   arr_size=5     i<=3
    // windosw size is 2
    // first maximum 2
    // second maximum 3
/*brute force start*/
int find_max_in_window(int arr[],int window_size,int start_index)
{
    int max=arr[start_index];
    for(int i=start_index;i<start_index+window_size;i++)
    {
        if(arr[i]>max)
        {
            max=arr[i];
        }
    }
    return max;
}

int* rolling_maximum_of_array_bruteforce(int arr[], int arr_size, int window_size, int& return_size)
{
    // Input validation
    if (window_size <= 0 || window_size > arr_size)
    {
        return_size = 0;
        return nullptr;
    }

    return_size=arr_size-window_size+1;
    int* output=new int[return_size];


    //i points to the element of the output
    for(int i=0;i<return_size;i++)
    {
        int max_i_window=find_max_in_window(arr,window_size,i);
        output[i]=max_i_window;
    }
    return output;
}
/*brute force ends*/

/*by heap*/
//ComFisrt for max heap
class CompFirst
{
public:
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b)
    {
        return a.first < b.first;
    }
};

int* rolling_maximum_of_array_heap(int arr[], int arr_size, int window_size, int& return_size)
{
    // Input validation
    if (window_size <= 0 || window_size > arr_size)
    {
        return_size = 0;
        return nullptr;
    }

    return_size = arr_size - window_size + 1;
    int* output = new int[return_size];

    //default Max-heap to store pairs of (value, index)
    std::priority_queue<std::pair<int, int>,std::vector<std::pair<int, int>>,CompFirst> max_heap;

    // Initialize the heap with the first window
    for (int i = 0; i < window_size; ++i)
    {
        max_heap.push({arr[i], i});
    }

    output[0] = max_heap.top().first;

    // Slide the window
        //i points to the end of the current window
    for (int i = window_size; i < arr_size; ++i)
    {
        // Add the new element to the heap
        max_heap.push({arr[i], i});

        // Remove elements that are outside the current window
        while (max_heap.top().second <= i - window_size)
        {
            max_heap.pop();
        }

        output[i - window_size + 1] = max_heap.top().first;
    }

    return output;
}
#endif //MICROSOFTINTERVIEW1_H
