#include <iostream>
#include <vector>

#include "algo.h"
#include "input.h"

std::vector<int> getIndices(int index){
    std::vector<int> out;
    if(index < 100 * 100 - 100){
        if (index%100 < 99){
            out.push_back(index + 101); // to the bottom right
        }
        out.push_back(index + 100); // right below
        if (index%100 > 0) {
            out.push_back(index + 99); // to the bottom left
        }
    }
    if (index%100 < 99){
        out.push_back(index + 1); // to the right
    }
    if (index%100 > 0) {
        out.push_back(index - 1 ); // to the left
    }
    if (index > 99 ) {
        if (index%100 < 99){
            out.push_back(index - 99); // to the top right
        }
        out.push_back(index - 100); // right above
        if (index%100 > 0) {
            out.push_back(index - 101); // to the top left
        }
    }
    return out;
}

int getNumberOfNeighborsOn(std::string lights , int index){
    auto indices = getIndices(index);
    return std::count_if(indices.begin(), indices.end(), [&lights](int n){return n >= 0 && static_cast<unsigned int>(n) <= lights.size() && lights[n] == '#';});

}

std::string transformLights(const std::string& lights, bool cornersStuckAtOn){
    std::string out;
    for(auto [light, index]: algo::enumerate(lights)){
        auto neighborsOn = getNumberOfNeighborsOn(lights, index);
        if (cornersStuckAtOn && (index == 0 || index == 99 || index == 9900 || index == 9999)){
            out += '#';
        }
        else if(light == '#'){
            out += (neighborsOn == 2 || neighborsOn == 3) ? '#' : '.';
        }
        else{
            out += (neighborsOn == 3) ? '#' : '.';
        }
    }
    return out;
}

int getNumberOfLightsOn(const std::string& lights, bool cornersStuckAtOn=false){
    std::string newLights = lights;
    for(int i = 0; i < 100; ++i){
        newLights = transformLights(newLights, cornersStuckAtOn);
    }
    return std::count_if(newLights.begin(), newLights.end(), [](char c){ return c == '#';});
}

int main(){
    auto lights = input::join(input::readMultiLineFile("input/input18.txt"));
    std::cout << getNumberOfLightsOn(lights)  << "\n";
    lights[0] = '#';
    lights[99] = '#';
    lights[9900] = '#';
    lights[9999] = '#';
    std::cout << getNumberOfLightsOn(lights, true)  << "\n";
}
