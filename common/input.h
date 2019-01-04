#ifndef INPUT_H_
#define INPUT_H_

#include <algorithm>
#include <functional>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

namespace input {
    //will throw an exception if the file is not found or if the file is empty
    std::string readSingleLineFile(const std::string& fileName);    
    std::vector<std::string> readMultiLineFile(const std::string& fileName);

    template<typename ReturnType, typename Callable>
    std::vector<ReturnType> transformMultiLineFile(const std::string& fileName, Callable transformer) {
        auto strings = readMultiLineFile(fileName);
        std::vector<ReturnType> out;
        std::transform(strings.begin(), strings.end(), std::back_inserter(out), transformer);
        return out;
    }
    
    std::vector<std::string> split(const std::string& str);
    std::vector<std::string> split(const std::string& str, char delimiter);
    std::vector<int> toNumbers(const std::string & str);
    int toNumber(const std::string& s);
    std::string dropTrailingComma(const std::string& str);

    std::string join(const std::vector<std::string>& v);
} // namespace input

#endif