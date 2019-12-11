#include <algorithm>
#include <iostream>

auto duplicateSearch(const std::string& candidate, size_t index = 0) {
    for(size_t i = index; i < candidate.length() - 1; ++i){
        if(candidate[i] == candidate[i + 1]) {
            return i+2;
        }
    }
    return std::string::npos;
}

bool hasDuplicates(const std::string& candidate) {
    auto i = duplicateSearch(candidate, 0);
    if(i != std::string::npos){
        return duplicateSearch(candidate, i) != std::string::npos;
    }
    return false;
}

bool hasThreeIncreasing(const std::string& candidate) {
    return ((candidate[0] == candidate[1] - 1 && candidate[1] == candidate[2] - 1) ||
            (candidate[1] == candidate[2] - 1 && candidate[2] == candidate[3] - 1) ||
            (candidate[2] == candidate[3] - 1 && candidate[3] == candidate[4] - 1) ||
            (candidate[3] == candidate[4] - 1 && candidate[4] == candidate[5] - 1) ||
            (candidate[4] == candidate[5] - 1 && candidate[5] == candidate[6] - 1) ||
            (candidate[5] == candidate[6] - 1 && candidate[6] == candidate[7] - 1));
}

bool isValid(const std::string & candidate){
    return hasDuplicates(candidate) && hasThreeIncreasing(candidate);
}

std::string getNextPassword(const std::string & s){
    std::string candidate = s;

    while(!isValid(candidate)){
        bool hasIncremented = false;
        size_t index = 7;
        while(!hasIncremented){
            if(candidate[index] == 'z'){
                candidate[index] = 'a';
                index --;
            }
            else {
                candidate[index]++;
                if (candidate[index] == 'i' || candidate[index] == 'o' || candidate[index] == 'l'){
                    candidate[index]++;
                }
                hasIncremented = true;
            }
        } 
    }
    return candidate;
}
int main(){
    std::cout << getNextPassword("vzbxkghb") << "\n";
    std::cout << getNextPassword("vzbxxzaa") << "\n";
    return 0;
}
