//
// Created by Adrian Hwang on 2024-08-24.
//
#include <string>
#include <iostream>
#include <vector>

#ifndef STRINGCOMP_KMP_H
#define STRINGCOMP_KMP_H
class StringComp_KMP
{
private:
    std::string ptrn_str=""; //pattern to be searched
    std::string main_str=""; //search pattern in the main_str
    std::vector<int> next; //a substring ptrn_str.substr(0,i+1) (i+1 is the length of the substring) has a prefix ending at index next[i] matching the suffix
    std::vector<int> found; //record the index of the first char of the found pattern
    void _init_next()
    {
        next.resize(ptrn_str.size(),-1); //resize to the size of the pattern string, and initialize all elements to -1
        next.push_back(-1);  //-1 represents non-exist, other values represent the index of the last matching character
        //the ptrn_str[0:1] has no matching substring

        int k=-1; //k is the index of the last matching character of prefix or suffix;
        //default k is -1, means no matching substring

        for(int i=1;i<ptrn_str.size();i++) //i points to the end of the substring
            //each loop, find the longest matching substring in ptrn_str[0,i+1]
            //each loop, k starting from next[i-1];
        {
            while( k!=-1 && ptrn_str[k+1]!=ptrn_str[i])
            //if the next element does not match, find the longest matching prefix in the substring
            //untile k=-1 or the next element matches
            {
                k=next[k];
            }
            if(ptrn_str[k+1]==ptrn_str[i])  //if matches, k+1 is the index of the last matching character
            {
                k++;
            }
            next[i]=k;
        }

        // for(int i=0;i<ptrn_str.size()-1;i++)  //i+1 is the length of the substring, i is the index of the last character of the substring
        // {
        //     //find the longest matching subsub....substring in ptrn_str.substr(0,i), and try to match ptrn_str[i+1]
        //     for(int j=i;j>=0;j=next[j])  //j is the index of the ending char in substring
        //     {
        //         if(ptrn_str[i+1]==ptrn_str[next[j]+1])
        //         {
        //             next.push_back(next[j]+1); //find the longest matching subsubstring matches the next element
        //             break;
        //         }
        //         //if j=0, and no matching subsubstring found, this means the next element does not match any prefix, so assign -1
        //         if(j==0)
        //         {
        //             next.push_back(-1);
        //             break;
        //         }
        //     }
        // }
    }

    void _print_next()
    {
        int i=0;
        std::cout<<"--------------next array is--------------"<<std::endl;
        for(std::vector<int>::iterator it=next.begin();it!=next.end();it++)
        {
            std::cout<<i<<"th element: "<<*it<<" ";
            i++;
        }
        std::cout<<std::endl;
        std::cout<<"------------------------------------------"<<std::endl;
    }

    void _init_found()
    {
        found.resize(main_str.size(),0);  //0 means not found, 1 means found
    }

    void _print_found()
    {
        std::cout<<"-------------Found pattern's first char index in main string are: -------------"<<std::endl;
        for(std::vector<int>::iterator it=found.begin();it!=found.end();it++)
        {
            std::cout<<*it<<" ";
        }
        std::cout<<std::endl;
    }

    //implement the KMP algorithm
    void _kmp()
    {
        int size_main=main_str.size();
        int size_ptrn=ptrn_str.size();
        int j=0; //j is the index of 1 past last matching character in the pattern string
        for(int i=0;i<size_main;i++) //scaning main string
        {
            if(main_str[i]==ptrn_str[j]) //matching
            {
                j++;
                if(j==size_ptrn) //if j reaches the end of the pattern string, a match is found
                //                      i
                //main_str  a b a b a e a b a e a
                //ptrn_str        b a e a
                //                        j
                {
                    int idx_found=i-size_ptrn+1;
                    std::cout<<"Pattern found at index: "<<idx_found<<std::endl;
                    //record the found pattern in found vector
                    found[idx_found]=1;
                    //reset j to 0, and continue to search the next pattern
                    j=0;
                }
            }else  //j points to the bad char in the pattern string
            {
                while(j>0)
                //termination condition
                //                       i
                //if j=0,      a b a b a e a b a c            main_str
                //                       a b a c              ptrn_str
                //                       j                 j keeps and i move 1 forward
                {
                    j=next[j-1]+1;  //j points to 1 past the last matching char of the prefix
                    if(main_str[i]==ptrn_str[j])
                    {
                        j++;
                        break;
                    }
                }
            }
        }
    }

public:
    StringComp_KMP(const std::string& main_str_input, const std::string& ptrn_str_input):main_str(main_str_input), ptrn_str(ptrn_str_input)
    {
        _init_next();
        _print_next();
        _init_found();
        _kmp();
        _print_found();
    }
};

#endif //STRINGCOMP_KMP_H
