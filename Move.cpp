//
// Created by matth on 6/9/2019.
//

#include "Move.h"
#include "Board.h"
#include <iostream>

BattleShip::Move::Move(const BattleShip::Player &maker) : maker(maker),
row(-99), col(-98), val('2'), shipHit('3'), hit() {}

BattleShip::Move::Move(const Player& maker, int row, int col) :
        maker(maker), row(row), col(col) {}

bool BattleShip::Move::isValid(const BattleShip::Board &board) const {
    return board.inBoundsFire(row, col);
}

void BattleShip::Move::make(BattleShip::Board &board) {
    board.setFire(row, col, getVal());
}

int& BattleShip::Move::getRow() {
    return row;
}

int& BattleShip::Move::getCol() {
    return col;
}

char BattleShip::Move::getVal() const {
    return val;
}

void BattleShip::Move::setVal(char value) {
    val = value;
}

void BattleShip::Move::setShipHit(char charHit) {
    shipHit = charHit;
}

char BattleShip::Move::getShipHit() const {
    return shipHit;
}

std::vector<std::tuple<int, int>> &BattleShip::Move::getPriorityHits4Ai()  {
    return priorityHits4Ai;
}

void BattleShip::Move::setHit(bool hit) {
    Move::hit = hit;
}

bool BattleShip::Move::isHit() const {
    return hit;
}

