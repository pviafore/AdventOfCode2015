#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <variant>

#include "input.h"

// helper type for the visitor #4
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

using WireOrValue = std::variant<uint16_t, std::string>;

WireOrValue toWireOrValue(const std::string& s){
    return std::isdigit(s[0]) != 0 ? WireOrValue(std::stoi(s)) : s;
}

enum class InstructionSize {
    NULLARY = 3,
    UNARY = 4,
    BINARY = 5
};

struct PowerSource{
    uint16_t value=0;
};

struct PassThrough{
    const std::string wire="";
};

struct BinaryGate {
    BinaryGate(const WireOrValue& wire1, const WireOrValue& wire2): wire1(wire1), wire2(wire2) {}
    const WireOrValue wire1 = std::string(), wire2 = std::string();
    [[nodiscard]] virtual uint16_t operate(uint16_t input1, uint16_t input2) const = 0;
};
struct AndGate : public BinaryGate{
    AndGate(const WireOrValue& wire1, const WireOrValue& wire2): BinaryGate(wire1, wire2) {}
    [[nodiscard]] uint16_t operate(uint16_t input1, uint16_t input2) const override {
        return input1 & input2;
    }
};
struct OrGate : public BinaryGate{
    OrGate(const WireOrValue& wire1, const WireOrValue& wire2): BinaryGate(wire1, wire2) {}
    [[nodiscard]] uint16_t operate(uint16_t input1, uint16_t input2) const override {
        return input1 | input2;
    }
};
struct UnaryGate {
    explicit UnaryGate(const std::string& wire): wire(wire) {}
    const std::string wire = "";
    [[nodiscard]] virtual uint16_t operate(uint16_t input) const = 0;
};
struct LeftShift : public UnaryGate{
    LeftShift(const std::string& wire, uint16_t value): UnaryGate(wire), shiftValue(value) {}
    const uint16_t shiftValue = 0;
    [[nodiscard]] uint16_t operate(uint16_t input) const override {
        return input << shiftValue;
    }
};
struct RightShift : public UnaryGate{
    RightShift(const std::string& wire, uint16_t value): UnaryGate(wire), shiftValue(value) {}
    const uint16_t shiftValue = 0;

    [[nodiscard]] uint16_t operate(uint16_t input) const override {
        return input >> shiftValue;
    }
};
struct NotGate : public UnaryGate{
    explicit NotGate(const std::string& wire): UnaryGate(wire) {}
    [[nodiscard]] uint16_t operate(uint16_t input) const override {
        return ~input;
    }
};

using WireInput = std::variant<PowerSource, PassThrough, AndGate, OrGate, LeftShift, RightShift, NotGate>;
struct WireInstruction {
    std::string wire;
    WireInput input;
};

WireInstruction toWireStructure(const std::string& s){
    const auto instructionString = input::split(s, ' ');
    const auto wire = *instructionString.rbegin();
    switch(instructionString.size()){
        case static_cast<size_t>(InstructionSize::NULLARY): {
            if(std::isdigit(instructionString[0][0]) != 0){
                const uint16_t value = std::stoi(instructionString[0]);
                return WireInstruction{wire, PowerSource{value}};
            }
            return WireInstruction{wire, PassThrough{instructionString[0]}};
        }
        case static_cast<size_t>(InstructionSize::UNARY):{
            return WireInstruction{wire, NotGate{instructionString[1]}};
        }
        case static_cast<size_t>(InstructionSize::BINARY): {
            const auto instruction = instructionString[1];
            if(instruction == "LSHIFT" || instruction == "RSHIFT"){
                const std::string inputWire = instructionString[0];
                const uint16_t value = std::stoi(instructionString[2]);
                const WireInput wireInput = (instruction == "LSHIFT") ? static_cast<WireInput>(LeftShift{inputWire, value}) : RightShift{inputWire, value};
                return {wire, wireInput}; 
            } 
            const WireOrValue inputWire1 = toWireOrValue(instructionString[0]);
            const WireOrValue inputWire2 = toWireOrValue(instructionString[2]);
            const WireInput wireInput = (instruction == "AND") ? static_cast<WireInput>(AndGate{inputWire1, inputWire2}) : OrGate{inputWire1, inputWire2}; 
            return {wire, wireInput}; 
        }
    }
    throw std::runtime_error("Should not reach here");
}

using WireGraph = std::map<std::string, WireInput>;
WireGraph buildWireGraph(const std::vector<WireInstruction>& instructions){
    WireGraph wireGraph;
    std::transform(instructions.begin(), instructions.end(), std::inserter(wireGraph, wireGraph.end()),
                    [](const auto& i){ return std::pair(i.wire, i.input); });
    return wireGraph;
}

std::map<std::string, uint16_t> cache;
uint16_t getWireValue(const WireGraph& wireGraph, const WireOrValue& wireOrValue)
{
    if(std::holds_alternative<uint16_t>(wireOrValue)){
        return std::get<uint16_t>(wireOrValue);
    }
    const auto& wire = std::get<std::string>(wireOrValue);

    auto result = cache.find(wire);
    if(result != cache.end()){
        return result->second;
    }

    WireInput wireInput = wireGraph.at(wire); 
    cache[wire] = std::visit(overloaded { 
        [](const PowerSource &ps){

            return ps.value;
        },
        [&wireGraph](const PassThrough &pt){
            return getWireValue(wireGraph, pt.wire);
        },
        [&wireGraph](const UnaryGate &gate){
            uint16_t value = getWireValue(wireGraph, gate.wire);
            return gate.operate(value);
        },
        [&wireGraph](const BinaryGate &gate){
            uint16_t value1 = getWireValue(wireGraph, gate.wire1);
            uint16_t value2 = getWireValue(wireGraph, gate.wire2);
            return gate.operate(value1, value2);
        }
    }, wireInput);
    return cache[wire];
}


int main(){
    const auto wireInstructions = input::transformMultiLineFile<WireInstruction>("input/input7.txt", toWireStructure);
    const auto wireGraph = buildWireGraph(wireInstructions);
    std::cout << getWireValue(wireGraph, "a") << "\n";
    auto newWireGraph = wireGraph;
    newWireGraph["b"] = PowerSource{getWireValue(wireGraph, "a")};
    cache.clear();
    std::cout << getWireValue(newWireGraph, "a") << "\n";

}
