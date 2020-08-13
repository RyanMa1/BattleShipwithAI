//
// Created by matth on 6/10/2019.
//

#include "HuntDestroyAiPlayer.h"
#include "Utility.h"
#include "Move.h"

BattleShip::HuntDestroyAiPlayer::HuntDestroyAiPlayer(const BattleShip::GameAttributes &gameAttributes) : AiPlayer(
        gameAttributes), priorityMoves(){
    getPossibleMoves();
    placeShips();
}

void BattleShip::HuntDestroyAiPlayer::getPossibleMoves() {

    for (int col = 0; col < board.getNumCols(); col++) {
        for (int row = 0; row < board.getNumRows(); row++) {
            setPossibleMoves(row,col);
        }
    }

}

void BattleShip::HuntDestroyAiPlayer::setPossibleMoves(int row, int col) {
    std::vector<int> pair;
    pair.push_back(row);
    pair.push_back(col);
    possibleMoves.push_back(pair);
}

BattleShip::Move BattleShip::HuntDestroyAiPlayer::getMove() {
    std::vector<int> pair;
    Move AiPossibleMove(*this);
    if(priorityMoves.empty()){
        int randomMove = getRandInt(0, possibleMoves.size(), randomNumberGenerator);
        pair = possibleMoves.at(randomMove);
        AiPossibleMove.getRow() = pair.at(0);
        AiPossibleMove.getCol() = pair.at(1);
        possibleMoves.erase(possibleMoves.begin() + randomMove);
        if(checkHit(AiPossibleMove.getRow(), AiPossibleMove.getCol())) {
            setPriorityMoves(pair);
            AiPossibleMove.setVal('X');
            AiPossibleMove.setHit(true);
            AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
            AiPossibleMove.make(getBoard());

        }else{
            AiPossibleMove.setVal('O');
            AiPossibleMove.setHit(false);
            AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
            AiPossibleMove.make(getBoard());
        }
    }else{
        for (int j = 0; j < priorityMoves.size(); j++) {
            pair = priorityMoves.at(j);
            for (int i = 0; i < possibleMoves.size(); i++) {
                if (priorityMoves.at(j) == possibleMoves.at(i)) {
                    AiPossibleMove.getRow() = priorityMoves.at(j).at(0);
                    AiPossibleMove.getCol() = priorityMoves.at(j).at(1);
                    priorityMoves.erase(priorityMoves.begin() + j);
                    if(checkHit(AiPossibleMove.getRow(), AiPossibleMove.getCol())) {
                        priorityMoves.clear();
                        setPriorityMoves(pair);
                        AiPossibleMove.setVal('X');
                        AiPossibleMove.setHit(true);
                        AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
                        AiPossibleMove.make(getBoard());

                    }else{
                        AiPossibleMove.setVal('O');
                        AiPossibleMove.setHit(false);
                        AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
                        AiPossibleMove.make(getBoard());
                    }
                }
            }
            //gets the element at the first tuple, from the vector of tuples of the priority hits...
        }
    }

    return AiPossibleMove;

}

const std::vector<std::vector<int>> &BattleShip::HuntDestroyAiPlayer::getPriorityMoves() const {
    return priorityMoves;
}

void BattleShip::HuntDestroyAiPlayer::setPriorityMoves(const std::vector<int> &pair) {
    //left
    priorityMoves.emplace_back((pair.at(0), pair.at(1) - 1));
    //top
    priorityMoves.emplace_back(pair.at(0) + 1, pair.at(1));
    //right
    priorityMoves.emplace_back(pair.at(0), pair.at(1) + 1);
    //bottom
    priorityMoves.emplace_back(pair.at(0) - 1,pair.at(1));
}

