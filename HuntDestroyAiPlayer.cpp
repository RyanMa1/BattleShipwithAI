//
// Created by matth on 6/10/2019.
//

#include "HuntDestroyAiPlayer.h"
#include "Utility.h"
#include "Move.h"

BattleShip::HuntDestroyAiPlayer::HuntDestroyAiPlayer(const BattleShip::GameAttributes &gameAttributes) : AiPlayer(
        gameAttributes){
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
    getPossibleMoves();
    Move AiPossibleMove(*this);
    //there are two vectors, priorityMoves and possibleMoves
    //priorityMoves: Used to check if the bot does hit a boat, then needs to check all around it to find the next part of boat
    std::cout << "In get Move()" << std::endl; 
    std::cout << "Is primoves empty? " << priorityMoves.empty() << std::endl;
    for(auto x : priorityMoves){
	std::cout <<"WIthin priority moves are the pair: " <<"row: " << x.at(0) <<"col: "  << x.at(1) << std::endl;
    } 
    if(priorityMoves.empty()){
        int randomMove = getRandInt(0, possibleMoves.size(), randomNumberGenerator);
	std::cout << possibleMoves.at(randomMove).at(0) <<  possibleMoves.at(randomMove).at(1)<< std::endl;
        pair = possibleMoves.at(randomMove);
        AiPossibleMove.getRow() = pair.at(0);
        AiPossibleMove.getCol() = pair.at(1);
	std::cout << "breaks?" << std::endl;	
        possibleMoves.erase(possibleMoves.begin() + randomMove);
        std::cout << "breaks? 2" << std::endl;
	std::cout << getName() << "'s size of queue"<< priorityMoves.size() << std::endl; 
	if(checkHit(AiPossibleMove.getRow(), AiPossibleMove.getCol())) {
            priorityMoves.push_back(pair);
	    std::cout << "in if statement" << std::endl; 
	    setPriorityMoves(pair);
	    AiPossibleMove.setVal('X');
            AiPossibleMove.setHit(true);
	    std::cout << "before setShipHit" << std::endl;
            AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
	    std::cout << "breaks after setting ship hit" << std::endl;
            AiPossibleMove.make(getBoard());
	
        }else{
            AiPossibleMove.setVal('O');
            AiPossibleMove.setHit(false);
            AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
            AiPossibleMove.make(getBoard());
        }
    }else{
 	std::cout << "in here breaking before for loop" << std::endl;	
	std::vector<std::vector<int>> oneWay;
	std::vector<std::vector<int>> secondWay;
	int destroyDir = 0;
	for (int i = 1; i < priorityMoves.size(); i++) {
            pair = priorityMoves.at(i);
	    AiPossibleMove.getRow() = pair.at(0);
	    AiPossibleMove.getCol() = pair.at(1);
	    std::cout << "checking is valid: "<< AiPossibleMove.isValid(getBoard()) << std::endl; 
	   //should only go into here to find the next ship letter 
	    if (checkHit(AiPossibleMove.getRow(), AiPossibleMove.getCol()){
//              getShipHealths[AiPossibleMove.getShipHit()] != 0)
//		AiPossibleMove.getRow() = priorityMoves.at(i).at(0);
//            	AiPossibleMove.getCol() = priorityMoves.at(i).at(1);
//
            	AiPossibleMove.setVal('X');
            	AiPossibleMove.setHit(true);
		std::cout << "in here breaking before setship 2" << std::endl;
            	AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
            	AiPossibleMove.make(getBoard()); 
	        destoryDir = i;	
		priorityMoves.erase(1,priorityMoves.size());
		break;
	    }else{
	        AiPossibleMove.setVal('O');
	        AiPossibleMove.setHit(false);
	        AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));	
		AiPossibleMove.make(getBoard());
		break;
		//priorityMoves.erase(priorityMoves.erase(priorityMoves.begin() + i);
	    }
            //gets the element at the first tuple, from the vector of tuples of the priority hits...
        }
    return AiPossibleMove;
    }
}

const std::deque<std::vector<int>> &BattleShip::HuntDestroyAiPlayer::getPriorityMoves() const {
    return priorityMoves;
}

void BattleShip::HuntDestroyAiPlayer::setPriorityMoves(const std::vector<int> &pair) {
    //left
    int row = pair.at(0);
    int col = pair.at(1);
    if(col - 1 >= 0){
	setPrioMoves(row, col - 1);
    }
    //top
    else if(pair.at(0) - 1 >= 0){
	 setPrioMoves(row - 1, col);
    }
    //right
    else if(pair.at(1) + 1 <= getBoard().getNumCols()){
    	setPrioMoves(row, col + 1);
    } 
    //bottom
    else if(pair.at(0) + 1 <=getBoard().getNumRows()){
    	setPrioMoves(col + 1, row);
    }
}
bool BattleShip::HuntDestroyAiPlayer::setNewPrioMoves(const int destroyDir, const std::vector<int> &pair){
    int row = pair.at(0);
    int col = pair.at(1);
    if(destroyDir % 2 == 0){
	while(checkHit(row, col) && row >= 0){
	    if(board.getFiringBoard().at(row).at(col) == getBlankChar()){
		setPrioMoves(row,col);
		row--;
	    }
	}
	while(checkHit(row, col) && row <= getBoard().getNumRows()){
	    if(board.getFiringBoard().at(row).at(col) == getBlankChar()){
		setPrioMoves(row,col);
		row++;
	    }
	}

    }
    else{	
	//B B B B
	//B X x B B
	//B B B X X
	//col - 2 because i pass in where it randomly hit, and we know there is a piece to left of boat. two pieces total
	while(checkHit(row, col) && col >= 0){
	    if(board.getFiringBoard().at(row).at(col) == getBlankChar()){ 
	        setPrioMoves(row,col);
	        col--;
	  }
	}
    	col = pair.at(1);
    	while(checkHit(row,col) && col <= getBoard().getNumCols()){
	    if(board.getFiringBoard().at(row).at(col) == getBlankChar()){
		setPrioMoves(row, col);
		col++;
	    }
	}
    }
	
}
void BattleShip::HuntDestroyAiPlayer::setPrioMoves(int row, int col){
    std::vector<int> pair;
    pair.push_back(row);
    pair.push_back(col);
    priorityMoves.push_back(pair);
}	
