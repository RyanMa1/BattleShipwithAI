//
// Created by matth on 6/9/2019.
//

#include "AiPlayer.h"
#include <sstream>
#include <ctime>
#include "Move.h"
#include "Utility.h"
#include "ShipPlacement.h"

int BattleShip::AiPlayer::nextAiId = 1;
std::mt19937 BattleShip::AiPlayer::randomNumberGenerator((time(nullptr)));

BattleShip::AiPlayer::AiPlayer(const GameAttributes &gameAttributes) :
        Player(gameAttributes), aiId(AiPlayer::nextAiId), possibleMoves() {
    setName();
    nextAiId++;
}



void BattleShip::AiPlayer::placeShips() {
    std::vector<char> orientation_choice{'h', 'v'};
    const int numRows = getBoard().getNumRows();
    const int numCols = getBoard().getNumCols();

    ShipPlacement placement;
    for(const auto& ship : shipHealths) {
        do {
            char orientation = *chooseRandom(orientation_choice, randomNumberGenerator);
            if (orientation == 'h') {
                placement.orientation = 'h';
                placement.shipSize = ship.second;
                placement.rowStart = getRandInt(0, numRows - 1, randomNumberGenerator);
                placement.colStart = getRandInt(0, numCols - ship.second, randomNumberGenerator);
                placement.rowEnd = placement.rowStart;
                placement.colEnd = placement.colStart + ship.second - 1;
            } else {
                placement.orientation = 'v';
                placement.shipSize = ship.second;
                placement.rowStart = getRandInt(0, numRows - ship.second, randomNumberGenerator);
                placement.colStart = getRandInt(0, numCols - 1, randomNumberGenerator);
                placement.rowEnd = placement.rowStart + ship.second - 1;
                placement.colEnd = placement.colStart;
            }
        }while(!getBoard().canPlaceShipAt(placement));
        getBoard().addShip(ship.first, placement);
        std::cout << getName() << "'s Board" << std::endl;
        getBoard().displayShipPlacement();
        std::cout << std::endl;
    }
}

void BattleShip::AiPlayer::setName() {
    std::stringstream name;
    name << "AI " << aiId;
    initializeName(name.str());
}

void BattleShip::AiPlayer::seed_random_number_generator(int seed) {
    BattleShip::AiPlayer::randomNumberGenerator.seed(seed);
}



void BattleShip::AiPlayer::setPossibleMoves(int row, int col) {
    AiPlayer::possibleMoves = possibleMoves;
}

void BattleShip::AiPlayer::getFiringBoard() {
    std::cout << getName() << "'s Board" << std::endl;
    getBoard().displayFiringBoard();
}

void BattleShip::AiPlayer::getPlacementBoard() {
    std::cout << getName() << "'s Board" << std::endl;
    getBoard().displayShipPlacement();
}

