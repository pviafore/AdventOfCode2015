#include <cassert>
#include <iostream>
#include <numeric>
#include <tuple>

#include "algo.h"
#include "input.h"
#include <functional>
using Dimensions = std::tuple<unsigned int, unsigned int, unsigned int>;
Dimensions toBox(const std::string& box) {
    const auto dimensions = input::split(box, 'x');
    if(dimensions.size() != 3) {
        throw std::runtime_error("Had more than 3 dimensions");
    }
    return {input::toNumber(dimensions[0]), input::toNumber(dimensions[1]), input::toNumber(dimensions[2])};
}

unsigned int getWrappingPaperNeeded(Dimensions dimensions) {
    const auto [length, width, height] = dimensions;
    return 2*width*height + 2*height*length + 2*length*width + std::min({length*width, width*height, height*length});
}

unsigned int getTotalWrappingPaperNeeded(const std::vector<Dimensions>& boxes) {
    const auto wrappingPaper = algo::map(boxes, getWrappingPaperNeeded);
    return std::accumulate(wrappingPaper.begin(), wrappingPaper.end(), 0u);
}

unsigned int getRibbonNeeded(Dimensions dimensions) {
    const auto [length, width, height] = dimensions;
    const auto largestDimension = std::max({length, width, height}); 
    return length * width * height + 2 * (length + width + height - largestDimension);
}

unsigned int getTotalRibbonNeeded(const std::vector<Dimensions>& boxes) {
    const auto ribbons = algo::map(boxes, getRibbonNeeded);
    return std::accumulate(ribbons.begin(), ribbons.end(), 0u);
}

int main() {
    const auto boxes = input::transformMultiLineFile<Dimensions>("input/input2.txt", toBox);
    std::cout << getTotalWrappingPaperNeeded(boxes) << " " << getTotalRibbonNeeded(boxes) << "\n";

}