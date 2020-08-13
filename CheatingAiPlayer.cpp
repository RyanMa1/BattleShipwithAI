//
// Created by matth on 6/10/2019.
//
#include <vector>
#include "Move.h"
#include "CheatingAiPlayer.h"
BattleShip::CheatingAiPlayer::CheatingAiPlayer(const BattleShip::GameAttributes &gameAttributes) :
AiPlayer(gameAttributes)
{
    placeShips();
}

void BattleShip::CheatingAiPlayer::getPossibleMoves() {
    for(int row = 0; row < board.getNumRows(); row++){
        for(int col = 0;  col < board.getNumCols(); col++){
            if(opponentBoard.at(row).at(col) != board.getBlankChar()){
                setPossibleMoves(row,col);
            }
        }
    }


}

void BattleShip::CheatingAiPlayer::setPossibleMoves(int row, int col) {
    std::vector<int> pair;
    pair.push_back(row);
    pair.push_back(col);
    possibleMoves.push_back(pair);
}

BattleShip::Move BattleShip::CheatingAiPlayer::getMove() {
    //cheating AI knows everything, all we need to do is set the
    getPossibleMoves();
    Move AiPlayerMove(*this);
    for (int i = 0; i < possibleMoves.size(); i++){
        if (board.getFiringBoard().at(possibleMoves.at(i).at(0)).at(possibleMoves.at(i).at(1)) == board.getBlankChar()){
            AiPlayerMove.getRow() = possibleMoves.at(i).at(0);
            AiPlayerMove.getCol() = possibleMoves.at(i).at(1);
            AiPlayerMove.setVal('X');
            AiPlayerMove.setHit(true);
            AiPlayerMove.setShipHit(opponentBoard.at(AiPlayerMove.getRow()).at(AiPlayerMove.getCol()));
            AiPlayerMove.make(getBoard());
            return AiPlayerMove;
        }
    }


}






