//
// Created by Adrian Hwang on 2024-09-02.
//

#ifndef MEETINGROOM_H
#define MEETINGROOM_H
#include <chrono>
class MeetingRoom
{
public:
    std::vector<std::vector<int>> intervals;
    std::vector<int> endTime; //store the end time of each meeting room
    MeetingRoom(const std::vector<std::vector<int>>& intervals_in, std::string mode):intervals(intervals_in)
    {
        //sort the intervals by start time
        __sort();
        //schedule time slot for each meeting room
        if(mode=="byArr") __schedule_byArr();
        else if(mode=="byMinHeap") __schedule_byMinHeap_vectorBased();
        else std::cout<<"invalid mode"<<std::endl;
        std::cout<<"meeting rooms number is: "<<endTime.size()<<std::endl;
    }
    //sort the intervals by start time
    void __sort()
    {
        std::cout<<"----------starting sorting intervals by starting time----------"<<std::endl;
        std::sort(intervals.begin(),intervals.end(),[](const std::vector<int>& a,const std::vector<int>& b)->bool
        {
            return a[0]<b[0];
        });
        //print
        for(auto& interval:intervals)
        {
            std::cout<<"("<<interval[0]<<","<<interval[1]<<")  ";
        }
        std::cout<<std::endl;
        std::cout<<"----------sorting is done----------"<<std::endl;
    }
    //schedule time for meeting room
    void __schedule_byArr()
    {
        std::cout<<"----------starting scheduling----------"<<std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        for(auto interval:intervals)
        {
            if(endTime.empty()) //no meeting room
            {
                endTime.push_back(interval[1]);
                continue; //proceed with another interval
            }
            //has meeting rooms
            int i=0;
            //find (in order of creation time) a meeting room available for the interval
            for(;i<endTime.size();i++)
            {
                if(interval[0]>=endTime[i])
                {
                    endTime[i]=interval[1]; //find available meeting room
                    break;
                }
            }
            //no available meeting room, create a new one
            if(i==endTime.size())//no available meeting room
            {
                endTime.push_back(interval[1]); //create a new meeting room
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time taken by arr: " << elapsed.count() << " seconds" << std::endl;
        std::cout<<"----------scheduling is done----------"<<std::endl;
    }
    //schedule time for meeting room by min heap
    // void __schedule_byMinHeap_pqBased()
    // {
    //     std::cout<<"----------starting scheduling----------"<<std::endl;
    //     for(auto interval:intervals)
    //     {
    //         if(endTime.empty()) //no meeting room
    //         {
    //             endTime.push_back(interval[1]);
    //             continue;
    //         }
    //         int i=0;
    //         for(;i<endTime.size();i++)
    //         {
    //             if(interval[0]>=endTime[i])
    //             {
    //                 endTime[i]=interval[1];
    //                 break;
    //             }
    //         }
    //         if(i==endTime.size())//no available meeting room
    //         {
    //             endTime.push_back(interval[1]);
    //         }
    //     }
    //     std::cout<<"----------scheduling is done----------"<<std::endl;
    // }
    //schedule time for meeting room by vector-based min heap
    //endTime is a minheap here
    void __schedule_byMinHeap_vectorBased(){
        std::cout<<"----------starting scheduling----------"<<std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        for(auto interval:intervals)
        {
            //no meeting room, create a new one
            if(endTime.empty())
            {
                endTime.push_back(interval[1]);
                continue;
            }

            //meeting room exists
            int earliest_end_time=endTime.front();  //get the meeting room with the earliest end time
            //if can use the meeting room with the earliest end time
            if(interval[0]>=earliest_end_time)
            {
                endTime[0]=interval[1]; //update the end time
                std::make_heap(endTime.begin(),endTime.end(),std::greater<int>()); //adjust the heap
            }else  //no available meeting room, create a new one
            {
                endTime.push_back(interval[1]);
                std::push_heap(endTime.begin(),endTime.end(),std::greater<int>()); //adjust the heap
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Time taken by minheap: " << elapsed.count() << " seconds" << std::endl;
        std::cout<<"----------scheduling is done----------"<<std::endl;
    }
};
#endif //MEETINGROOM_H
