#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_set>
#include <vector>

#include "algo.h"
#include "geometry.h"
#include "input.h"

geometry::Point to_point_direction(char direction) {
    if (direction == '<') { return { -1, 0}; }
    if (direction == '>') { return { 1, 0}; }
    if (direction == 'v') { return { 0, 1}; }
    if (direction == '^') { return { 0, -1}; }
    throw std::runtime_error("The input given in was incorrect");
}

template <typename Container>
std::vector<geometry::Point> getHousesReached(const Container& directions) {
    std::vector<geometry::Point> houses = { {0, 0} };
    std::transform(directions.begin(), directions.end(), std::back_inserter(houses), to_point_direction);
    std::partial_sum(houses.begin(), houses.end(), houses.begin());
    return houses;
}

int getNumberOfUniqueHouses(const std::vector<geometry::Point>& houses) {
    return std::unordered_set<geometry::Point, geometry::Hash>(houses.begin(), houses.end()).size();
}

int getNumberOfUniqueHousesWithRoboSanta(const std::string& directions) {
    auto santa = algo::range(directions.begin(), directions.end(), 2);
    auto roboSanta = algo::range(directions.begin() + 1, directions.end(), 2);
    auto houses = getHousesReached(santa);
    auto roboHouses = getHousesReached(roboSanta);
    std::unordered_set<geometry::Point, geometry::Hash> uniqueHouses(houses.begin(), houses.end()); 
    uniqueHouses.insert(roboHouses.begin(), roboHouses.end());
    return uniqueHouses.size();
}

int main() {
    auto directions = input::readSingleLineFile("input/input3.txt");
    auto houses = getHousesReached(directions);
    std::cout << getNumberOfUniqueHouses(houses) << " " << getNumberOfUniqueHousesWithRoboSanta(directions) << "\n";

}