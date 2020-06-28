#include <iostream>

#include <iostream>
#include <set>
#include <tuple>
#include <vector>

#include "input.h"

using Solutions = std::vector<int>;
using ContainerIterator = std::vector<int>::iterator;

Solutions getSolutions(int target, int containersUsedSoFar, ContainerIterator start, ContainerIterator end){
    Solutions solutions;
    for(auto iter = start; iter != end; ++iter){
        auto containerSize = *iter;
        if(containerSize == target){
            // base case - this is our solution
            solutions.push_back(containersUsedSoFar + 1);
        }
        if(containerSize < target) {
            auto nextSolutions = getSolutions(target - containerSize, containersUsedSoFar + 1, iter + 1, end); 
            solutions.insert(solutions.end(), nextSolutions.begin(), nextSolutions.end());
        }
    }
    return solutions;
}

Solutions getPartitions(int target, std::vector<int> containers){
    return getSolutions(target, 0, containers.begin(), containers.end());
}

int getNumberOfMinimumSolutions(Solutions solutions){
    auto minSolution = *std::min_element(solutions.begin(), solutions.end());
    return std::count_if(solutions.begin(), solutions.end(), [minSolution](auto s){ return s == minSolution; });
}

int main() {
    auto containers = input::transformMultiLineFile<int>("input/input17.txt", input::toNumber);
    auto solutions = getPartitions(150, containers);
    std::cout << solutions.size() << " " << getNumberOfMinimumSolutions(solutions) << "\n";
}
