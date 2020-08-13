//
// Created by matth on 6/9/2019.
//

#include <iostream>
#include <string>
#include "Board.h"
#include "ShipPlacement.h"
#include "Move.h"

BattleShip::Board::Board(const int &rowSize, const int &columnSize) :
        firingBoard(rowSize, std::string(columnSize, '*')),
        placementBoard(rowSize, std::string(columnSize, '*')),
        blankChar('*')
{

}


int BattleShip::Board::getNumRows() const {
    return firingBoard.size();
}


int BattleShip::Board::getNumCols() const {
    return firingBoard.size();
}

bool BattleShip::Board::canPlaceShipAt(ShipPlacement &shipPlacement) {
    return overlap(shipPlacement);
}

bool BattleShip::Board::overlap(ShipPlacement &shipPlacement) {
    if (inBoundsBoatSet(shipPlacement)){
        if (shipPlacement.getOrientation() == 'h'){
            for (int i = shipPlacement.getColStart(); i < (shipPlacement.getColEnd()+1); i++){
                if (placementBoard.at(shipPlacement.getRowStart()).at(i) != getBlankChar()){
                    return false;
                }
            }
        }else{
            for (int j = shipPlacement.getRowStart(); j < (shipPlacement.getRowEnd()+1); j++){
                if (placementBoard.at(j).at(shipPlacement.getColStart()) != getBlankChar()){
                    return false;
                }
            }
        }
        return true;
    }
    return false;

}

void BattleShip::Board::addShip(char symbol, ShipPlacement &shipPlacement) {
    if (shipPlacement.getOrientation() == 'h'){
        setBoatHoriz(shipPlacement.getRowStart(), shipPlacement.getColStart(), shipPlacement.getShipSize(), symbol);
    }
    else if (shipPlacement.getOrientation() == 'v'){
        setBoatVert(shipPlacement.getRowStart(), shipPlacement.getColStart(), shipPlacement.getShipSize(), symbol);
    }
}

void BattleShip::Board::setBoatHoriz(const int &row, const int &colStart, const int &shipSize, const char &val) {
    for (int i = colStart; i < (colStart + shipSize);  i++){
        placementBoard.at(row).at(i) = val;
    }
}

void BattleShip::Board::setBoatVert(const int &row, const int &col, const int &shipSize, const char &val) {
    for (int i = row; i < (row + shipSize); i ++){
        placementBoard.at(i).at(col) = val;
    }
}


bool BattleShip::Board::inBoundsBoatSet(ShipPlacement &shipPlacement) {
    return (shipPlacement.getColStart() >= 0) && (shipPlacement.getColEnd() < getNumCols())
           && (shipPlacement.getRowStart() >= 0) && (shipPlacement.getRowEnd() < getNumRows());

}



bool BattleShip::Board::inBoundsFire(const int &row, const int &col) const {
    return isBetween(row, col, getNumRows() - 1);
}

bool BattleShip::Board::isBetween(const int &row, const int &col, const int &boardSize) const {
    return (row >= 0 && row <= boardSize) && (col >= 0 && col <= boardSize);
}



void BattleShip::Board::displayFiringBoard() const {
    std::cout << "  ";
    for (int i = 0; i < getNumRows(); i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    int rowIndex = 0;
    for (const auto& row : firingBoard) {
        std::cout << rowIndex << " ";
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        rowIndex++;
        std::cout << std::endl;
    }

}

void BattleShip::Board::displayShipPlacement() const {
    std::cout << "  ";
    for (int i = 0; i < getNumRows(); i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    int rowIndex = 0;
    for (const auto& row : placementBoard) {
        std::cout << rowIndex << " ";
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        rowIndex++;
        std::cout << std::endl;
    }
}

void BattleShip::Board::setFire(const int &row, const int &col, const char &val) {
    firingBoard.at(row).at(col) = val;
}
//
//bool BattleShip::Board::checkHit(const int &row, const int &col) {
////    if(placementBoard.at(row).at(col) != getBlankChar()){
////        return true;
////    }else{
////        return false;
////    }
//    return placementBoard.at(row).at(col) != getBlankChar();
//}

const char BattleShip::Board::getBlankChar() const {
    return blankChar;
}

const char &BattleShip::Board::at(const int &row, const int &col) const {
    return placementBoard.at(row).at(col);
}

std::vector<std::string> & BattleShip::Board::getFiringBoard(){
    return firingBoard;
}

const std::vector<std::string> &BattleShip::Board::getPlacementBoard() const {
    return placementBoard;
}

void BattleShip::Board::updatePlacementBoard(Move &move) {
    placementBoard.at(move.getRow()).at(move.getCol()) = move.getVal();

}
