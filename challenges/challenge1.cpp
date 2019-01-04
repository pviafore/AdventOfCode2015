#include <iostream>
#include <numeric>

#include "algo.h"
#include "input.h"

auto getFinalFloor(const std::vector<int>& instructions) {
    return std::accumulate(instructions.begin(), instructions.end(), 0);
}

auto getFirstIndexThatMovesToBasement(const std::vector<int>& instructions) {
    auto startFloor = 0;
    for(auto [instruction, index] : algo::enumerate(instructions)) {
        startFloor += instruction;
        if(startFloor == -1) {
            return index + 1;
        }
    }
    throw std::runtime_error("We should never reach this line of code");
}
int toDirection(char parens) {
    return (parens == '(') ? 1 : -1;
}
int main() {
    const auto instructions = algo::map(input::readSingleLineFile("input/input1.txt"), toDirection);
    std::cout << getFinalFloor(instructions) <<  " " << getFirstIndexThatMovesToBasement(instructions) << "\n"; 
    return 0;
}