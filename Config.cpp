//
// Created by matth on 6/9/2019.
//
#include <string>
#include "Config.h"

std::vector<std::string> BattleShip::configGame(const std::string &filename) {
    std::vector<std::string> gameConfig;
    std::ifstream in;
    in.open(filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)){
        gameConfig.push_back(line);
    }
    return gameConfig;


}

std::vector<std::string> BattleShip::readfile(const std::string &filename) {
    std::ifstream in;
    in.open(filename);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)){
        lines.push_back(line);
    }
    return lines;
}