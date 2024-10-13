//
// Created by Adrian Hwang on 2024-09-24.
//

#ifndef ALLPATHSFROMSOURCETOTARGET_H
#define ALLPATHSFROMSOURCETOTARGET_H
#include <iostream>

const int N=10; //number of nodes
const int N2=6; //number of nodes

/*Whether AllPathsFromSourceToTarget_dag_memo*/
bool dfs_dag_memo(int cur_node,int dest_node,int edges[N][N],int memo[N]);
bool AllPathsFromSourceToTarget_dag_memo(int edges[N][N]){
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
    bool result=dfs_dag_memo(src_node,dest_node,edges,memo);
    return result;
}
//traverse all paths from src_node to dest_node
//memo and edges are paassed by reference
bool dfs_dag_memo(int cur_node,int dest_node,int edges[N][N],int memo[N]) //return true if all paths are open from cur_node to dest_node
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
            bool result=dfs_dag_memo(i,dest_node,edges,memo); //check all paths from i to dest_node
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

/*Whether AllPathsFromSourceToTarget_dag_noMemo*/
bool dfs_dag_noMemo(int cur_node, int dest_node, int edges[N][N]);
bool AllPathsFromSourceToTarget_dag_noMemo(int edges[N][N]){
    //set source node and destination node
    int src_node=0;
    int dest_node=N-1;

    //dfs from src_node
    bool result=dfs_dag_noMemo(src_node,dest_node,edges);
    return result;
}
bool dfs_dag_noMemo(int cur_node, int dest_node, int edges[N][N])
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
            bool result=dfs_dag_noMemo(i,dest_node,edges);
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

/*Whether AllPathsFromSourceToTarget_cyclic_memo*/
bool dfs_cyclic_memo(int cur_node,int dest_node,int edges[N2][N2],std::vector<int>& visited,std::vector<int>& memo);
bool AllPathsFromSourceToTarget_cyclic_memo(int edges[N2][N2])
{
    //-1: UNVISITED, 0: VISITING, 1: VISITED
    std::vector<int> visited(N2,-1);

    //memo[i]=-1: not calculated, 0: at least one path is closed, 1: all paths are open
    std::vector<int> memo(N2,-1);

    //source node and destination node
    int src_node=0;
    int dest_node=3;
    bool result=dfs_cyclic_memo(src_node,dest_node,edges,visited,memo);
    return result;
}
bool dfs_cyclic_memo(int cur_node,int dest_node,int edges[N2][N2],std::vector<int>& visited,std::vector<int>& memo)
{
    //if all paths from cur_node to dest_node are already calculated, return the calculated result
    if(memo[cur_node]!=-1)
    {
        return memo[cur_node]==1?true:false;
    }

    //found dest_node, return true
    if(cur_node==dest_node)
    {
        return true;
    }

    //find a cycle, but cycle may also lead to the destination node, so backtrack and don't modify memo[cur_node]
    if(visited[cur_node]==0)
    {
        return true;
    }

    //mark cur_node as visiting
    visited[cur_node]=0; //if the recursively traversal encounter the same node, it means a cycle (the logic is dealt with above)

    //traverse all paths from cur_node to dest_node
    bool deadend=true;
    for(int i=0;i<N2;i++)
    {
        //if cur_node is connected to i
        if( edges[cur_node][i]) //even if visited, still step into the node, the dfs will return false
        {
            //find outgoings
            deadend=false;

            //dfs from i
            bool result=dfs_cyclic_memo(i,dest_node,edges,visited,memo);
            if(!result) //if any path is not open, return false. The returning false will be propagated to the src_ndoe
            {
                memo[cur_node]=0; //fail
                return false;
            }
        }
    }

    //mark current node as visited
    visited[cur_node]=1;

    //after traversing, no return, so all paths are open from cur_node to dest_node or cur_node is a deadend
    if(deadend)
    {
        memo[cur_node]=0;
        return false;
    }else //all paths are open
    {
        memo[cur_node]=1;
        return true;
    }
}


void dfs_findAllPaths_cyclic_memo(int cur_node,int dest_node,int edges[N2][N2],std::vector<int>& visited,std::vector<std::vector<int>>& paths, std::vector<int>& path);
void FindAllPathsFromSrc2Dest_cyclic_memo(int edges[N2][N2])
{
    //0: non-visiting, 1: visiting
    std::vector<int> visited(N2,0);

    //Valid Paths
    std::vector<std::vector<int>> paths;

    //path
    std::vector<int> path;

    //source node and destination node
    int src_node=0;
    int dest_node=3;
    dfs_findAllPaths_cyclic_memo(src_node,dest_node,edges,visited,paths,path);

    //print starting signal
    std::cout<<"FindAllPathsFromSrc2Dest_cyclic_memo, pop outside of loop:"<<std::endl;
    //print all paths
    std::cout<<"Valid paths are: "<<std::endl;
    for(int i=0;i<paths.size();i++)
    {
        for(int j=0;j<paths[i].size();j++)
        {
            if(j!=paths[i].size()-1) std::cout<<paths[i][j]<<"->";
            else std::cout<<paths[i][j]<<std::endl;
        }
    }
    //print path
    std::cout<<"remaining path is: "<<std::endl;
    for(int i=0;i<path.size();i++)
    {
        if(i!=path.size()-1) std::cout<<path[i]<<"->";
        else std::cout<<path[i]<<std::endl;
    }

}
void dfs_findAllPaths_cyclic_memo(int cur_node, int dest_node, int edges[N2][N2], std::vector<int>& visited,std::vector<std::vector<int>>& paths,std::vector<int>& path)
{
    visited[cur_node]=1; //mark as visiting
    path.push_back(cur_node); //keep track of current path
    if(cur_node==dest_node) //find the destination node, add it to paths
    {
        paths.push_back(path);
    }else //no destination, traversal subsequent nodes
    {
        for(int i=0;i<N2;i++)
        {
            if(edges[cur_node][i]==1) //connected
            {
                if(visited[i]!=1) //only traverse unvisited nodes
                {
                    dfs_findAllPaths_cyclic_memo(i,dest_node,edges,visited,paths,path);
                }
            }
        }
    }
    //backtrack: has traversed all subsequent nodes, pop the current node
    path.pop_back();
    visited[cur_node]=0; //mark as not visiting
}

void dfs_findAllPaths_cyclic_memo_popInLoop(int cur_node,int dest_node,int edges[N2][N2],std::vector<int>& visited,std::vector<std::vector<int>>& paths, std::vector<int>& path);
void FindAllPathsFromSrc2Dest_cyclic_memo_popInLoop(int edges[N2][N2])
{
    //0: non-visiting, 1: visiting
    std::vector<int> visited(N2,0);

    //Valid Paths
    std::vector<std::vector<int>> paths;

    //path
    std::vector<int> path;

    //source node and destination node
    int src_node=0;
    int dest_node=3;
    dfs_findAllPaths_cyclic_memo_popInLoop(src_node,dest_node,edges,visited,paths,path);

    //print starting signal
    std::cout<<"FindAllPathsFromSrc2Dest_cyclic_memo, pop inside loop:"<<std::endl;
    //print all paths
    std::cout<<"Valid paths are: "<<std::endl;
    for(int i=0;i<paths.size();i++)
    {
        for(int j=0;j<paths[i].size();j++)
        {
            if(j!=paths[i].size()-1) std::cout<<paths[i][j]<<"->";
            else std::cout<<paths[i][j]<<std::endl;
        }
    }

    //print path
    std::cout<<"remaining path's size "<<std::endl;
    // for(int i=0;i<path.size();i++)
    // {
    //     //i is not the last element
    //     if(i!=path.size()-1) std::cout<<path[i]<<"->";
    //     else std::cout<<path[i]<<std::endl;
    // }
    // for(auto i=path.begin();i
    std::cout<< path.size() <<std::endl;
}
void dfs_findAllPaths_cyclic_memo_popInLoop(int cur_node, int dest_node, int edges[N2][N2], std::vector<int>& visited,std::vector<std::vector<int>>& paths,std::vector<int>& path)
{
    visited[cur_node]=1; //mark as visiting
    path.push_back(cur_node); //keep track of current path
    if(cur_node==dest_node) //find the destination node, add it to paths
    {
        paths.push_back(path);
    }else //no destination, traversal subsequent nodes
    {
        for(int i=0;i<N2;i++)
        {
            if(edges[cur_node][i]==1) //connected
            {
                if(visited[i]!=1) //only traverse unvisited nodes
                {
                    dfs_findAllPaths_cyclic_memo(i,dest_node,edges,visited,paths,path);
                    path.pop_back();
                }
            }
        }
    }
    //backtrack: has traversed all subsequent nodes, pop the current node
    visited[cur_node]=0; //mark as not visiting
}








#endif //ALLPATHSFROMSOURCETOTARGET_H
