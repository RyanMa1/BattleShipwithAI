//
// Created by matth on 6/9/2019.
//

#include <vector>
#include <string>
#include <cstdlib>
#include <map>
#include <iostream>
#include "GameAttributes.h"

BattleShip::GameAttributes::GameAttributes(const std::vector<std::string> &gameFile) :
        rowSize(std::stoi(gameFile[0])), colSize(std::stoi(gameFile[1])), numBoats(std::stoi(gameFile[2]))
{
    for (int i = 3; i < gameFile.size(); i++){
        gameAttributes.push_back(gameFile.at(i));
    }
    getShipAttributes(gameFile);


}

int BattleShip::GameAttributes::getSize() const{
    return gameAttributes.size();
}

void BattleShip::GameAttributes::getShipAttributes(const std::vector<std::string> &gameFile) {
    char boat;

    int boatLength;
    for (int i = 3; i < gameFile.size(); i++){
        boat = gameFile.at(i).at(0);
        const char placeholder = gameFile.at(i).at(2);
        // WE MIGHT NEED TO CONVERT CHAR INTO A INT
        boatLength = std::atoi(&placeholder);
        shipAttributes.emplace(boat, boatLength);
    }
}

const std::map<char, int> &BattleShip::GameAttributes::getShipAttributes() const {
    return shipAttributes;
}

int BattleShip::GameAttributes::getRowSize() const {
    return rowSize;
}

int BattleShip::GameAttributes::getColSize() const {
    return colSize;
}

int BattleShip::GameAttributes::getNumBoats() const {
    return numBoats;
}
