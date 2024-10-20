//
// Created by Adrian Hwang on 2024-10-19.
//
//opeartor
//     op1    op2
//       \    /
//        op3
//        /  \
//      op4  op5
//       /
//     op6
//print the order of the operators
//op1, op2, op3, op4, op6, op5

#ifndef OPERATORPATH_H
#define OPERATORPATH_H
#include <unordered_map>
#include <vector>
namespace OperatorOrder
{
    class OperatorOrder
    {
    public:
        enum class Operator : int
        {
            Op1=1,
            Op2,
            Op3,
            Op4,
            Op5,
            Op6
        };
        std::unordered_map<Operator,std::vector<Operator>> Graph; //stored in ajdacent list
        std::vector<Operator> order; //op1, op2, op3, op4, op6, op5
        OperatorOrder()
        {
            build_adjacent_list();
            topological_sort();
            print_order();
        }
        void build_adjacent_list()
        {
            Graph[Operator::Op1] = {Operator::Op3};
            Graph[Operator::Op2] = {Operator::Op3};
            Graph[Operator::Op3] = {Operator::Op4, Operator::Op5};
            Graph[Operator::Op4] = {Operator::Op6};
            Graph[Operator::Op5] = {};
            Graph[Operator::Op6] = {};
        }
        bool topological_sort()
        {
            //0: not visited, 1: visiting, 2: visited
            //initialize visiting to false
            std::unordered_map<Operator,int> visited;
            for(int i=1;i<=static_cast<int>(Operator::Op6);i++)
            {
                visited[static_cast<Operator>(i)] = 0;
            }

            //find in_degree 0 as starting node
            std::unordered_map<Operator,int> in_degree;
            for(auto pair: Graph)
            {
                for(auto node: pair.second)
                {
                    in_degree.find(node) == in_degree.end()? in_degree[node] = 0:in_degree[node]++;
                }
            }
            std::vector<Operator> start_nodes;
            for(auto pair : in_degree)
            {
                if(pair.second == 0) start_nodes.push_back(pair.first);
            }

            //DFS
            std::vector<std::vector<Operator>> paths(start_nodes.size());
            int i=0;
            for(auto start_node: start_nodes)
            {
                if(!dfs(start_node,visited,paths[i++])) return false;
            }
            //concatenate the paths
            std::vector<Operator>::iterator it[start_nodes.size()];
            for(int j=0;j<start_nodes.size();j++)
            {
                it[j] = paths[j].begin();
            }
            int count=0;
            while(count<Graph.size())
            {
                //add non-joint nodes to order
                for(int i=0;i<start_nodes.size();i++)
                {
                    while(it[i]!=paths[i].end() && in_degree[*it[i]]<2)
                    {
                        order.push_back(*it[i]);
                        it[i]++;
                        count++;
                    }
                }
                //add joint nodes to order
                for(int i=0;i<start_nodes.size();i++)
                {
                    while(it[i]!=paths[i].end() && in_degree[*it[i]]>=2)
                    {
                        order.push_back(*it[i]);
                        it[i]++;
                        count++;
                    }
                }
            }
            return true;
        }
        bool dfs(Operator cur_node, std::unordered_map<Operator,int>& visited, std::vector<Operator>& path)
        {
            //pre_order
            if(visited[cur_node]==1) return false; //cycle
            else if(visited[cur_node]==2) return true; //visited
            else //not visited, visited[cur_node]==0
            {
                path.push_back(cur_node);

                //in_order
                visited[cur_node] = 1;
                for(auto adj_node: Graph[cur_node])
                {
                    if(!dfs(adj_node,visited,path)) return false; //cycle, stop all the way back
                }

                //post
                //after all the children are visited, mark the node as visited
                visited[cur_node] = 2;
                return true;
            }
        }
        // Function to convert enum values to strings
        std::string to_string(Operator op)
        {
            switch (op)
            {
            case Operator::Op1: return "Op1";
            case Operator::Op2: return "Op2";
            case Operator::Op3: return "Op3";
            case Operator::Op4: return "Op4";
            case Operator::Op5: return "Op5";
            case Operator::Op6: return "Op6";
            default: return "Unknown";
            }
        }
        void print_order()
        {
            for(auto node:order)
            {
                std::cout<<to_string(node)<<" ";
            }
            std::cout<<std::endl;
        }
    };
}
#endif //OPERATORPATH_H
