//
// Created by Adrian Hwang on 2024-11-13.
//

#ifndef UOMAP_EQUALITY_HASHFUN_H
#define UOMAP_EQUALITY_HASHFUN_H
//
// Created by Adrian Hwang on 2024-11-11.
//


#include <iostream>
#include <unordered_map>
#include <memory>
#include <functional>

class FunctionCache
{
    class Parameters // private inner class
    {
    public:
        Parameters(int first, int second)
            : first(first), second(second) {}

        int first;
        int second; // public member variable

        // Define equality operator for Parameters
        bool operator==(const Parameters &other) const {
            return first == other.first && second == other.second;
        }
    };

    // Hash function for Parameters
    struct ParametersHash {
        std::size_t operator()(const Parameters& params) const {
            return std::hash<int>()(params.first) ^ std::hash<int>()(params.second);
        }
    };

public:
    // Constructor
    FunctionCache(std::function<int(int, int)> function) : function(function) {}

    int calculate(int first, int second)
    {
        Parameters args(first, second); // use std::make_shared
        auto it = calculations.find(args); //it is iterator to the key-value pair
        if (it != calculations.end()) //if the key is found
            return it->second; //return the value

        //if key is not found, calculate the value and store it in the map
        int calculation = function(first, second);
        calculations[args] = calculation;
        return calculation;
    }

private:
    std::unordered_map<Parameters, int, ParametersHash> calculations;
    std::function<int(int, int)> function;
};

#ifndef RunTests

int modulo(int a, int b)
{
    std::cout << "Function modulo has been called.\\n";
    return a % b;
}

#endif
#endif //UOMAP_EQUALITY_HASHFUN_H
