#include <iostream>
#include <numeric>
#include <string>

#include "algo.h"
#include "input.h"

std::string processEscapedString(const std::string& s){
    std::string newString;

    for(auto iter = s.begin(); iter != s.end(); ++iter){
        char c = *iter;

        if(c == '"'){
            continue;
        }
        if(*iter == '\\'){
            c = *++iter;
            if(c == 'x'){
                char tens = *++iter;
                if(iter == s.end()){
                    throw std::runtime_error("Invalid input");
                }
                char ones = *++iter;
                if(iter == s.end()){
                    throw std::runtime_error("Invalid input");
                }
                c = static_cast<char>((tens - '0') * 10 + (ones - '0'));
            }
        }
        newString += std::string(1, c);
    }
    return newString;
}

std::string escapeString(const std::string & s){
    std::string newString = "\"";
    std::for_each(s.begin(), s.end(), [&newString](char c){
       if(c == '\\' || c == '"'){
           newString += "\""; 
       } 
       newString += std::string(1, c);
    });
    return newString + "\"";
}

int main() {
    const auto lines = input::readMultiLineFile("input/input8.txt");
    const std::string text = std::accumulate(lines.begin(), lines.end(), std::string());
    const std::string newText = processEscapedString(text);
    std::cout << "Size is " << text.size() - newText.size();

    const auto newLines = algo::map(lines, escapeString);
    const std::string escapedText = std::accumulate(newLines.begin(), newLines.end(), std::string());
    std::cout << "Size is " << escapedText.size() - text.size() << "\n";


}
