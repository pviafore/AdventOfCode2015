#include <iostream>
#include <tuple>

#include "input.h"

struct Ingredient{
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
};

Ingredient toIngredient(const std::string& s){
    auto split = input::split(s, ' ');
    return Ingredient{std::stoi(split[2]), std::stoi(split[4]), std::stoi(split[6]), std::stoi(split[8]), std::stoi(split[10])};
}

unsigned int getBestScore(const std::vector<Ingredient> & ingredients, int32_t calorieTarget=0){
    //assume four ingredients
    int bestScore = 0;
    for (int a = 0; a < 100; ++a){
        for (int b = 0; b < 100 - a; ++b) {
            for (int c = -0; c < 100 - a - b; ++c) {
                int d = 100 - a - b - c;
                int score = std::max(0, ingredients[0].capacity*a + ingredients[1].capacity*b + ingredients[2].capacity*c + ingredients[3].capacity*d) *
                            std::max(0, ingredients[0].durability*a + ingredients[1].durability*b + ingredients[2].durability*c + ingredients[3].durability*d) *
                            std::max(0, ingredients[0].flavor*a + ingredients[1].flavor*b + ingredients[2].flavor*c + ingredients[3].flavor*d) *
                            std::max(0, ingredients[0].texture*a + ingredients[1].texture*b + ingredients[2].texture*c + ingredients[3].texture*d);
                auto calories = ingredients[0].calories*a + ingredients[1].calories*b + ingredients[2].calories*c + ingredients[3].calories*d;
                if (calorieTarget == 0 || calories == calorieTarget){
                    bestScore = std::max(score, bestScore);
                }
            }
        }
    }
    return bestScore;

}

int main(){
    auto ingredients = input::transformMultiLineFile<Ingredient>("input/input15.txt", toIngredient);
    std::cout << getBestScore(ingredients) << "\n";
    std::cout << getBestScore(ingredients, 500) << "\n";
    return 0;
}
