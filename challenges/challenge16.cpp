#include <iostream>
#include <optional>

#include "input.h"

struct Aunt {
    unsigned int number;
    std::optional<int> children = std::optional<int>();
    std::optional<int> cats = std::optional<int>();
    std::optional<int> samoyeds = std::optional<int>();
    std::optional<int> pomeranians = std::optional<int>();
    std::optional<int> akitas = std::optional<int>();
    std::optional<int> vizslas = std::optional<int>();
    std::optional<int> goldfish = std::optional<int>();
    std::optional<int> trees = std::optional<int>();
    std::optional<int> cars = std::optional<int>();
    std::optional<int> perfumes = std::optional<int>();

    [[nodiscard]]
    bool matches(const Aunt& aunt) const{
        return (!aunt.children || this->children == aunt.children) &&
               (!aunt.cats || this->cats == aunt.cats) &&
               (!aunt.samoyeds || this->samoyeds == aunt.samoyeds) &&
               (!aunt.pomeranians || this->pomeranians == aunt.pomeranians) &&
               (!aunt.akitas || this->akitas == aunt.akitas) &&
               (!aunt.vizslas || this->vizslas == aunt.vizslas) &&
               (!aunt.goldfish || this->goldfish == aunt.goldfish) &&
               (!aunt.trees || this->trees == aunt.trees) &&
               (!aunt.cars || this->cars == aunt.cars) &&
               (!aunt.perfumes || this->perfumes == aunt.perfumes);

    }
    
    [[nodiscard]]
    bool matches_v2(const Aunt& aunt) const{
        return (!aunt.children || this->children == aunt.children) &&
               (!aunt.cats || this->cats < aunt.cats) &&
               (!aunt.samoyeds || this->samoyeds == aunt.samoyeds) &&
               (!aunt.pomeranians || this->pomeranians > aunt.pomeranians) &&
               (!aunt.akitas || this->akitas == aunt.akitas) &&
               (!aunt.vizslas || this->vizslas == aunt.vizslas) &&
               (!aunt.goldfish || this->goldfish > aunt.goldfish) &&
               (!aunt.trees || this->trees < aunt.trees) &&
               (!aunt.cars || this->cars == aunt.cars) &&
               (!aunt.perfumes || this->perfumes == aunt.perfumes);
    }
    

};

Aunt toAunt(const std::string& text){
    auto split = input::split(text, ' ');
    Aunt aunt{static_cast<unsigned int>(std::stoi(split[1]))};

    for (auto iter = split.cbegin()+2; iter != split.cend(); ++iter){
        if (*iter == "children:"){
            aunt.children = std::stoi(*(++iter));
        }
        if (*iter == "cats:"){
            aunt.cats = std::stoi(*(++iter));
        }
        if (*iter == "samoyeds:"){
            aunt.samoyeds = std::stoi(*(++iter));
        }
        if (*iter == "akitas:"){
            aunt.akitas = std::stoi(*(++iter));
        }
        if (*iter == "pomeranians:"){
            aunt.pomeranians = std::stoi(*(++iter));
        }
        if (*iter == "vizslas:"){
            aunt.vizslas = std::stoi(*(++iter));
        }
        if (*iter == "cars:"){
            aunt.cars = std::stoi(*(++iter));
        }
        if (*iter == "trees:"){
            aunt.trees = std::stoi(*(++iter));
        }
        if (*iter == "goldfish:"){
            aunt.goldfish = std::stoi(*(++iter));
        }
        if (*iter == "perfumes:"){
            aunt.perfumes = std::stoi(*(++iter));
        }
    }

    return aunt;
}

int main(){
    auto aunts = input::transformMultiLineFile<Aunt>("input/input16.txt", toAunt);
    Aunt optimalAunt = {0, 3, 7, 2, 3, 0, 0, 5, 3, 2, 1};
    std::cout << std::find_if(aunts.begin(), aunts.end(), [optimalAunt](const Aunt& aunt){
        return optimalAunt.matches(aunt);
    })->number << "\n";
    std::cout << std::find_if(aunts.begin(), aunts.end(), [optimalAunt](const Aunt& aunt){
        return optimalAunt.matches_v2(aunt);
    })->number << "\n";
    return 0;
}
