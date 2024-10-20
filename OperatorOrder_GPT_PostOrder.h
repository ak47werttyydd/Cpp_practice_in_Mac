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

#ifndef OPERATORORDER_GPT_H
#define OPERATORORDER_GPT_H

#include <unordered_map>
#include <vector>
#include <iostream>
namespace OperatorOrder_GPT
{
    class OperatorOrder
    {
    public:
        enum class Operator : int
        {
            Op1 = 1,
            Op2,
            Op3,
            Op4,
            Op5,
            Op6
        };

        std::unordered_map<Operator, std::vector<Operator>> Graph; // Adjacency list
        std::vector<Operator> order; // Final order of operators

        OperatorOrder()
        {
            build_adjacent_list();
            if (topological_sort())
            {
                print_order();
            }
            else
            {
                std::cout << "Cycle detected, no valid topological sort." << std::endl;
            }
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
            std::unordered_map<Operator, int> visited; // 0: not visited, 1: visiting, 2: visited
            for (int i = 1; i <= static_cast<int>(Operator::Op6); ++i)
            {
                visited[static_cast<Operator>(i)] = 0;
            }

            // Perform DFS from every unvisited node
            for (int i = 1; i <= static_cast<int>(Operator::Op6); ++i)
            {
                if (visited[static_cast<Operator>(i)] == 0)
                {
                    if (!dfs(static_cast<Operator>(i), visited))
                    {
                        return false; // Cycle detected
                    }
                }
            }
            std::reverse(order.begin(), order.end()); // Reverse to get the correct topological order
            return true;
        }

        bool dfs(Operator cur_node, std::unordered_map<Operator, int> &visited)
        {
            if (visited[cur_node] == 1)
                return false; // Cycle detected
            if (visited[cur_node] == 2)
                return true;  // Already visited

            visited[cur_node] = 1; // Mark as visiting
            for (auto adj_node : Graph[cur_node])
            {
                if (!dfs(adj_node, visited))
                    return false; // Cycle detected
            }

            visited[cur_node] = 2; // Mark as fully visited
            order.push_back(cur_node); // Post-order insertion
            return true;
        }

        // Function to convert enum values to strings
        std::string to_string(Operator op)
        {
            switch (op)
            {
            case Operator::Op1:
                return "Op1";
            case Operator::Op2:
                return "Op2";
            case Operator::Op3:
                return "Op3";
            case Operator::Op4:
                return "Op4";
            case Operator::Op5:
                return "Op5";
            case Operator::Op6:
                return "Op6";
            default:
                return "Unknown";
            }
        }

        void print_order()
        {
            for (auto node : order)
            {
                std::cout << to_string(node) << " ";
            }
            std::cout << std::endl;
        }
    };
}
#endif // OPERATORORDER_GPT_H
