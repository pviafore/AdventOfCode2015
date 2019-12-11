#include <algorithm>
#include <iostream>

#include "input.h"

struct Reindeer {
    int speed;
    int flightTime;
    int restTime;
    int distanceTravelled;
    int points;

    bool isFlying(int tick){
        return tick % (flightTime + restTime) < flightTime;
    }
    bool isResting(int tick){
        return tick % (flightTime + restTime) >= flightTime;
    }
};

Reindeer toReindeer(const std::string & s) {
    auto reindeer = input::split(s, ' ');
    return Reindeer{std::stoi(reindeer[3]), std::stoi(reindeer[6]), std::stoi(reindeer[13]), 0, 0};
}

Reindeer race(std::vector<Reindeer> reindeer, int target){
    for(auto& r: reindeer) {
        int rounds = target / (r.flightTime + r.restTime);
        int timeRemaining = target - (rounds * (r.flightTime + r.restTime));
        r.distanceTravelled = rounds * r.speed * r.flightTime + ((r.isFlying(timeRemaining)) ? timeRemaining * r.speed : r.speed*r.flightTime);
    }
    return *std::max_element(reindeer.begin(), reindeer.end(),[](auto r1, auto r2){ return r1.distanceTravelled < r2.distanceTravelled;});
} 

Reindeer raceWithPoints(std::vector<Reindeer> reindeer, int target){
    for(int tick = 0; tick < target; ++tick){
        for(auto& r: reindeer) {
            if(r.isFlying(tick)){
                r.distanceTravelled += r.speed;
            }
        }
        auto greatest = *std::max_element(reindeer.begin(), reindeer.end(), [] (auto r1, auto r2) { 
            return r1.distanceTravelled < r2.distanceTravelled;
        });
        for(auto& r: reindeer) {
            if (r.distanceTravelled == greatest.distanceTravelled){
                r.points++;
            }
        }
    }
    return *std::max_element(reindeer.begin(), reindeer.end(),[](auto r1, auto r2){ return r1.points < r2.points;});
} 

int main(){
    auto reindeer = input::transformMultiLineFile<Reindeer>("input/input14.txt", toReindeer);
    std::cout << race(reindeer, 2503).distanceTravelled << "\n";
    std::cout << raceWithPoints(reindeer, 2503).points << "\n";
    return 0;
}
