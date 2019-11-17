#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "input.h"


std::vector<std::string> makeDoubles() {
    std::vector<std::string> letters;
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::transform(alphabet.begin(), alphabet.end(), std::back_inserter(letters), [](char letter) {
        return std::string(1, letter) + letter;
    });
    return letters;
}



bool hasDoubles(const std::string& candidate) {
    const std::vector<std::string> doubles = makeDoubles();
    return std::any_of(doubles.begin(), doubles.end(),
                        [candidate](const std::string& d) {
                            return candidate.find(d) != std::string::npos;
                        });
}

bool hasNoDisallowedSequences(const std::string& candidate) {
    const std::vector<std::string> disallowed = {"ab", "cd", "pq", "xy"};
    return std::all_of(disallowed.begin(), disallowed.end(),
                        [candidate](const std::string& d){
                            return candidate.find(d) == std::string::npos;
                        });
}

bool hasThreeVowels(const std::string& candidate) {
    const std::string vowels = "aeiou";
    return std::count_if(candidate.begin(), candidate.end(), [&vowels](char c) {
        return vowels.find(c) != std::string::npos; 
    }) >= 3;
}

bool isNice(const std::string& candidate) {
    return hasDoubles(candidate) && hasNoDisallowedSequences(candidate) &&
           hasThreeVowels(candidate); 
}

bool isNiceImproved(const std::string& candidate) {
    std::regex doubledUp("([a-z]{2}).*\\1");
    std::regex repeats("([a-z])[a-z]\\1");
    std::smatch m;
    return std::regex_search(candidate, m, doubledUp) && std::regex_search(candidate, m, repeats);
}

int main() {
    auto words = input::readMultiLineFile("input/input5.txt");
    std::cout << std::count_if(words.begin(), words.end(), isNice) << "\n";
    std::cout << std::count_if(words.begin(), words.end(), isNiceImproved) << "\n";

}
