#include <iostream>
#include <numeric>
#include <string>

#include "algo.h"

std::string process(const std::string &candidate){
    auto grouped = algo::groupby(candidate);
    return std::accumulate(grouped.begin(), grouped.end(), std::string(), [](auto accum, const auto& group){
        return accum + std::to_string(group.size()) + std::string(1, *group.begin());
    });
}

int getLengthOfResult(const std::string& s, int times){
    auto candidate = s;
    for(int i = 0; i < times; ++i){
        candidate = process(candidate);
    }
    return candidate.length();

}

int main() { 
    std::cout << getLengthOfResult("1321131112", 40) << "\n";
    std::cout << getLengthOfResult("1321131112", 50) << "\n";

    return 0;
}
