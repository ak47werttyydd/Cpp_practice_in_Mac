//
// Created by Adrian Hwang on 2024-09-24.
//

#ifndef ALLPATHSFROMSOURCETOTARGET_H
#define ALLPATHSFROMSOURCETOTARGET_H
#include <iostream>
using namespace std;

const int N=10; //number of nodes
bool dfs(int cur_node,int dest_node,int edges[N][N],int memo[N]);
bool dfs_noMemo(int cur_node, int dest_node, int edges[N][N]);
bool AllPathsFromSourceToTarget(int edges[N][N]){
    //initialize memo[N] to -1
    //memo[i]=-1 means the path from node i to node N-1 is not calculated yet
    //memo[i]= 0 means not all paths from node i to node N-1 are open
    //memo[i]= 1 means all paths from node i to node N-1 are open
    int memo[N];
    for(int i=0;i<N;i++)
    {
        memo[i]=-1;
    }

    //set source node and destination node
    int src_node=0;
    int dest_node=N-1;

    //dfs from src_node
    bool result=dfs(src_node,dest_node,edges,memo);
    return result;
}
bool AllPathsFromSourceToTarget_noMemo(int edges[N][N]){
    //set source node and destination node
    int src_node=0;
    int dest_node=N-1;

    //dfs from src_node
    bool result=dfs_noMemo(src_node,dest_node,edges);
    return result;
}

//traverse all paths from src_node to dest_node
//memo and edges are paassed by reference
bool dfs(int cur_node,int dest_node,int edges[N][N],int memo[N]) //return true if all paths are open from cur_node to dest_node
{
    //if the path from cur_node to dest_node is already calculated, return the calculated result
    if(memo[cur_node]!=-1)
    {
        return memo[cur_node]; //0 for fail, 1 for success
    }

    //if cur_node is the destination node, return true
    if(cur_node==dest_node)
    {
        memo[cur_node]=1;
        return true;
    }

    //if cur_node is not the destination node, check all paths from cur_node to dest_node
    bool deadend=true; //assume cur_node is not outgoing
    for(int i=0;i<N;i++)
    {
        if(edges[cur_node][i]) //connected
        {
            deadend=false; //has outgoing
            bool result=dfs(i,dest_node,edges,memo); //check all paths from i to dest_node
            if(!result) //if any path is not open, return false
            {
                memo[cur_node]=0; //fail
                return false; //return false
            }
        }
    }

    //all paths are open from cur_node to dest_node or cur_node is a deadend
    if(deadend) //if deadend
    {
        memo[cur_node]=0; //fail
        return false;
    }else //all paths are open
    {
        memo[cur_node]=1;
        return true;
    }
}

bool dfs_noMemo(int cur_node, int dest_node, int edges[N][N])
{
    if(cur_node==dest_node)
    {
        return true;
    }

    bool deadend=true;
    //traverse
    for(int i=0;i<N;i++)
    {
        if(edges[cur_node][i]) //connected
        {
            deadend=false;
            bool result=dfs_noMemo(i,dest_node,edges);
            if(!result) //if any path is not open, return false
            {
                return false; //return false
            }
        }
    } //no return false, so that dead end or all paths are open

    if(deadend) //if deadend
    {
        return false;
    }

    return true;
}

#endif //ALLPATHSFROMSOURCETOTARGET_H
