#include "input.h"
#include <iostream>
#include <map>
#include <numeric>
#include <string>

const unsigned int GRID_SIZE=1000U;
enum class Action {
    TURN_ON,
    TOGGLE,
    TURN_OFF
};

using Point = std::pair<unsigned int, unsigned int>;

struct Instruction {
    Action action;
    Point upperLeft, lowerRight;
};

Point getPointFromString(const std::string& s){
    const auto split = input::split(s, ',');
    return {std::stoi(split[0]), std::stoi(split[1])};
}

Instruction toInstruction(const std::string& s){
    std::cout << s <<std::endl;
    const auto split = input::split(s);
    if (split.size() == 4) {
        return {Action::TOGGLE, getPointFromString(split[1]), getPointFromString(split[3])};
    }
    const auto action = split[1] == "on" ? Action::TURN_ON : Action::TURN_OFF;
    return {action, getPointFromString(split[2]), getPointFromString(split[4])};
}
class Light {
public:
    Light() {
        state = false;
    }

    void changeState(Action action){
        switch(action){
            case Action::TURN_OFF:
                state = false;
                break;
            case Action::TURN_ON:
                state = true;
                break;
            case Action::TOGGLE:
                state = !state;
                break;
        }

    }
    
    [[nodiscard]] bool isOn() const {
        return state;
    }
    
    [[nodiscard]] unsigned int getBrightness() const {
        return state ? 1 : 0;
    }
private:
    bool state;
};
class BrightnessLight {
public:
    BrightnessLight() {
        state = 0;
    }

    void changeState(Action action){
        switch(action){
            case Action::TURN_OFF:
                if(state != 0){
                    state -= 1;
                }
                break;
            case Action::TURN_ON:
                state += 1;
                break;
            case Action::TOGGLE:
                state += 2;
                break;
        }
    }
    
    [[nodiscard]] bool isOn() const {
        return state > 0;
    }

    [[nodiscard]] unsigned int getBrightness() const {
        return state;
    }
private:
    unsigned int state;
};

template<typename T>
class Lights {
public:
     Lights(){
         for(auto i = 0U; i < GRID_SIZE; ++i){
            for(auto j = 0U; j < GRID_SIZE; ++j){
                lights[{i,j}] = T();
            }
        } 
    }

    void applyInstruction(Instruction instruction){
        auto [x1, y1] = instruction.upperLeft;
        auto [x2, y2] = instruction.lowerRight;
        for(auto x = x1; x <= x2; ++x){
            for(auto y=y1; y <= y2; ++y) {
                lights[{x,y}].changeState(instruction.action);
            }
        }
    }

    size_t getNumberOfLightsTurnedOn(){
        return std::count_if(lights.begin(), lights.end(), [](const auto& l){return l.second.isOn();});
    }

    unsigned int getTotalBrightness() {
        return std::accumulate(lights.begin(), lights.end(), 0U, [](auto count, const auto& light){
            return count + light.second.getBrightness();
        });
    }

private:
    std::map<Point, T> lights;

};


int main(){
    auto instructions = input::transformMultiLineFile<Instruction>("input/input6.txt", toInstruction);
    Lights<Light> lights;
    std::for_each(instructions.begin(), instructions.end(), [&lights](const auto& inst) {
        lights.applyInstruction(inst);
    });
    std::cout << lights.getNumberOfLightsTurnedOn() << "\n";
    Lights<BrightnessLight> lights2;
    std::for_each(instructions.begin(), instructions.end(), [&lights2](const auto& inst) {
        lights2.applyInstruction(inst);
    });
    std::cout << lights2.getTotalBrightness() << "\n";
    return 0;
}
