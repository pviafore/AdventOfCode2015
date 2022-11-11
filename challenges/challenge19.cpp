#include <cctype>
#include <iostream>
#include <map>
#include <set>

#include "input.h"

using Mappings = std::vector<std::pair<std::string, std::string>>;
using SplitMappings = std::vector<std::pair<std::string, std::vector<std::string>>>;

std::set<std::string> getDistinctMolecules(const std::string& molecule, const Mappings & mappings){
    std::set<std::string> out;
    for(const auto& [candidate, replacement]: mappings){
        auto iter = molecule.begin();
        while (iter != molecule.end()) {
            iter = std::search(iter, molecule.end(), candidate.begin(), candidate.end());
            if(iter != molecule.end()){
                out.insert(std::string(molecule.begin(), iter) + replacement + std::string(iter + candidate.size(), molecule.end()));
                iter++;
            }
        }
    }
    return out;
}

int getStepsNeededToReachMolecule(const std::string& molecule, const SplitMappings& mappings){
    // find all potential matches that match first letter
    // for every match that we have, we now have a target molecule to synthesize
    // try to synthesize the beginning of the module until we hit a match.
    // Remember, once we have a match, it can be an exact match (keep trying)
    // or we need to synthesize to get a match
    //Once we have a match,
    // replace it, then start over again

    auto molecules = toMolecules(molecule);
    std::vector<std::string> matches;
    std::copy_if(mappings.begin(), mappings.end(), std::back_inserter(matches),
                 [](const auto& transformation){ return does_molecule_start_with(transformation)});
    return 0;

}

std::pair<std::string, std::string> toMapping(const std::string& text){
    auto text_parts = input::split(text);
    return {text_parts[0], text_parts[2]};
}

std::vector<std::string> toMolecules(const std::string& text) {
    std::vector<std::string> molecules;
    for(std::size_t index = 0; index < text.length(); ++index) {
        if (index + 1 < text.length() && islower(text[index + 1]) != 0){
            molecules.push_back(text.substr(index, 2));
            index += 1;
        }
        else {
            molecules.push_back(text.substr(index, 1));
        }
    }
    return molecules;
}

int main(){
    auto text = input::readMultiLineFile("input/input19.txt");
    auto molecule = *text.rbegin();
    Mappings mappings;
    std::transform(text.begin(), text.end() - 1, std::inserter(mappings, mappings.begin()), toMapping);
    auto distinctMolecules = getDistinctMolecules(molecule, mappings);
    std::cout << distinctMolecules.size() << "\n";

    SplitMappings reverseMappings;
    std::transform(mappings.begin(), mappings.end(), std::inserter(reverseMappings, reverseMappings.begin()), [](auto p){ return std::pair(p.first, toMolecule(p.first));});
    std::cout << getStepsNeededToReachMolecule(molecule, reverseMappings) << "\n";


    return 0;
}
