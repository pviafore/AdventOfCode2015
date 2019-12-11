#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>

#include "algo.h"
#include "input.h"

using Segment = std::pair<std::string, std::string>;
using Route = std::pair<Segment, uint32_t>;
using RouteMap = std::map<Segment, uint32_t>;

Route toRoute(const std::string& s) {
    auto words = input::split(s);
    return Route{ {words[0], words[2]}, std::stoi(words[4]) };
}

std::vector<std::string> getDestinations(const RouteMap& routeMap){
    std::set<std::string> out;
    std::transform(routeMap.begin(), routeMap.end(), std::inserter(out, out.begin()), [](auto s){ return s.first.first; });
    std::transform(routeMap.begin(), routeMap.end(), std::inserter(out, out.begin()), [](auto s){ return s.first.second; });
    return std::vector(out.begin(), out.end());
}

int getDistance(const RouteMap& routeMap, std::vector<std::string> path){
    auto first = path.begin();
    auto second = path.begin() + 1;
    int sum = 0;
    while(second != path.end()){
        auto segment = Segment{*first, *second};
        sum += (routeMap.find(segment) != routeMap.end()) ? routeMap.at(segment) : routeMap.at({*second, *first});
        first = second++;
    }
    return sum;
}

int getShortestRoute(const RouteMap& routeMap){
    auto destinations = getDestinations(routeMap);
    int shortest = INT32_MAX;
    do{
        shortest = std::min(shortest, getDistance(routeMap, destinations));
    } while(std::next_permutation(destinations.begin(), destinations.end()));
    return shortest;

}

int getLongestRoute(const RouteMap& routeMap) {
    auto destinations = getDestinations(routeMap);
    int longest = -1;
    do{
        longest = std::max(longest, getDistance(routeMap, destinations));
    } while(std::next_permutation(destinations.begin(), destinations.end()));
    return longest;
}

int main() {
    auto routes = input::transformMultiLineFile<Route>("input/input9.txt", toRoute);
    RouteMap routeMap = std::map(routes.begin(), routes.end());
    std::cout << getShortestRoute(routeMap) << "\n";
    std::cout << getLongestRoute(routeMap) << "\n";
}
