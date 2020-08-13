//
// Created by matth on 6/9/2019.
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "Player.h"
#include "Board.h"
#include "GameAttributes.h"



BattleShip::Player::Player(const GameAttributes &gameAttributes):
        playerName(), board(gameAttributes.getRowSize(), gameAttributes.getColSize()),
        shipHealths(gameAttributes.getShipAttributes())
{}

BattleShip::Board &BattleShip::Player::getBoard() {
    return board;
}

const std::string &BattleShip::Player::getName() const {
    return playerName;
}

void BattleShip::Player::initializeName(const std::string &name) {
    playerName = name;
}

void BattleShip::Player::setOpponentBoard(BattleShip::Board &board) {
    copy(board.getPlacementBoard().begin(), board.getPlacementBoard().end(), back_inserter(opponentBoard));

}

bool BattleShip::Player::checkHit(const int &row, const int &col) {
    char fire = opponentBoard.at(row).at(col);
    return fire != board.getBlankChar();

}

void BattleShip::Player::updateShipHealth(char val, std::string playersName1, std::string playersName2) {
    shipHealths[val] = shipHealths[val] - 1;
    for(auto& ship : shipHealths){
        if(ship.second == 0){
            std::cout << playersName1 << " destroyed " << playersName2 << "'s " << val << "!" << "\n" << std::endl;
            shipHealths.erase(ship.first);
        }else{
            continue;
        }
    }

}

const std::map<char, int> &BattleShip::Player::getShipHealths() const {
    return shipHealths;
}

void BattleShip::Player::clearOpponentBoard() {
    opponentBoard.clear();
}
