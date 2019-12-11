#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "input.h"

using Couple = std::pair<std::string, std::string>;
using Relationship = std::pair<Couple, int>;

Relationship toRelationship(const std::string& s){
    auto split = input::split(s, ' ');
    int multiplier = (split[2] == "gain") ? 1 : -1;
    return { {split[0], std::string(split[10].begin(), split[10].end() - 1)}, std::stoi(split[3]) * multiplier};
}

std::vector<std::string> getNames(const std::vector<Relationship>& relationships){
    std::set<std::string> out;
    std::transform(relationships.begin(), relationships.end(), std::inserter(out, out.begin()), [](auto r){
        return r.first.first;
    });
    return std::vector<std::string>(out.begin(), out.end());
}

int calculateHappiness(const std::map<Couple, int>& relationshipMap, const std::vector<std::string>& names){

    int total = 0;
    for(size_t i = 0; i < names.size(); ++i){
        total += relationshipMap.at({names[i], names[(i+1)% names.size()]});
        total += relationshipMap.at({names[i], names[(i + names.size() - 1) % names.size()]});
    }
    return total;
}

int getMaximumHappiness(const std::vector<Relationship>& relationships){
    auto names = getNames(relationships);
    std::map<Couple, int> relationshipMap(relationships.begin(), relationships.end());
    int maxHappiness = -1;
    do {
        maxHappiness = std::max(maxHappiness, calculateHappiness(relationshipMap, names)); 
    } while(std::next_permutation(names.begin(), names.end()));
    return maxHappiness;
}

int getMaximumHappinessWithMe(const std::vector<Relationship>& relationships){
    auto names = getNames(relationships);
    std::map<Couple, int> relationshipMap(relationships.begin(), relationships.end());
    for(const auto& name: names){
        relationshipMap[{"Me", name}] = 0;
        relationshipMap[{name, "Me"}] = 0;
    }
    names.emplace_back("Me");
    std::sort(names.begin(), names.end());
    int maxHappiness = -1;
    do {
        maxHappiness = std::max(maxHappiness, calculateHappiness(relationshipMap, names)); 
    } while(std::next_permutation(names.begin(), names.end()));
    return maxHappiness;
}


int main(){
    auto relationships = input::transformMultiLineFile<Relationship>("input/input13.txt", toRelationship);
    std::cout << getMaximumHappiness(relationships) << "\n";
    std::cout << getMaximumHappinessWithMe(relationships) << "\n";
    return 0;
}
