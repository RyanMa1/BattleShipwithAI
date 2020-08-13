//
// Created by matth on 6/10/2019.
//
#include <sstream>
#include <ctime>
#include "RandomAiPlayer.h"

#include "Move.h"
BattleShip::RandomAiPlayer::RandomAiPlayer(const BattleShip::GameAttributes &gameAttributes) : AiPlayer(gameAttributes)
{
    placeShips();
}

void BattleShip::RandomAiPlayer::getPossibleMoves() {

    for (int col = 0; col < board.getNumCols(); col++) {
        for (int row = 0; row < board.getNumRows(); row++) {
            setPossibleMoves(row,col);
        }
    }
}

void BattleShip::RandomAiPlayer::setPossibleMoves(int row, int col) {
    std::vector<int> pair;
    pair.push_back(row);
    pair.push_back(col);
    possibleMoves.push_back(pair);

}


BattleShip::Move BattleShip::RandomAiPlayer::getMove() {
    std::vector<int> pair;
    getPossibleMoves();
    Move AiPossibleMove(*this);
    int randomMove = getRandInt(0, possibleMoves.size(), randomNumberGenerator);
    pair = possibleMoves.at(randomMove);
    AiPossibleMove.getRow() = pair.at(0);
    AiPossibleMove.getCol() = pair.at(1);
    possibleMoves.erase(possibleMoves.begin() + randomMove);
    if(checkHit(AiPossibleMove.getRow(), AiPossibleMove.getCol())) {
        AiPossibleMove.setHit(true);
        AiPossibleMove.setVal('X');
        AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
        AiPossibleMove.make(getBoard());
    }else{
        AiPossibleMove.setVal('O');
        AiPossibleMove.setHit(false);
        AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
        AiPossibleMove.make(getBoard());
    }
    return AiPossibleMove;
}
