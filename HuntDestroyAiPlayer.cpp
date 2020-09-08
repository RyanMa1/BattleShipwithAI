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
    std::cout << "Num cols: "<< getBoard().getNumCols() << std::endl;
    //there are two vectors, priorityMoves and possibleMoves
    //priorityMoves: Used to check if the bot does hit a boat, then needs to check all around it to find the next part of boat
    std::cout << "In get Move()" << std::endl; 
    std::cout << "Is primoves empty? " << priorityMoves.empty() << std::endl;
//    for(auto x : priorityMoves){
//	std::cout <<"WIthin priority moves are the pair: " <<"row: " << x.at(0) <<"col: "  << x.at(1) << std::endl;
//    } 
    if(!killBothWays.empty()){
	priorityMoves.erase(priorityMoves.begin(), priorityMoves.end());
	std::cout << "in killBothWays.empty" << std::endl;
	std::cout << "size of priorityMoves: "<< priorityMoves.size()  << std::endl;	
	for(int i = 0; i < killBothWays.size(); i++){
	   if (board.getFiringBoard().at(killBothWays.at(i).at(0)).at(killBothWays.at(i).at(1)) == board.getBlankChar()){
            AiPossibleMove.getRow() = killBothWays.at(i).at(0);
            AiPossibleMove.getCol() = killBothWays.at(i).at(1);
            AiPossibleMove.setVal('X');
            AiPossibleMove.setHit(true);
            AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
            AiPossibleMove.make(getBoard());
            killBothWays.pop_front();
            return AiPossibleMove; 
	}
	}
    }else if(priorityMoves.empty()){
        int randomMove = getRandInt(0, possibleMoves.size(), randomNumberGenerator);
	//std::cout << possibleMoves.at(randomMove).at(0) <<  possibleMoves.at(randomMove).at(1)<< std::endl;
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
	    return AiPossibleMove;	
        }else{
            AiPossibleMove.setVal('O');
            AiPossibleMove.setHit(false);
            AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
            AiPossibleMove.make(getBoard());
	    return AiPossibleMove;
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
	    std::cout << "PrioMovesChoices: " << AiPossibleMove.getRow() << " , " << AiPossibleMove.getCol() << std::endl; 
	    if (checkHit(AiPossibleMove.getRow(), AiPossibleMove.getCol()) && opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()) == opponentBoard.at(priorityMoves.at(0).at(0)).at(priorityMoves.at(0).at(1))){
//              getShipHealths[AiPossibleMove.getShipHit()] != 0)
//		AiPossibleMove.getRow() = priorityMoves.at(i).at(0);
//            	AiPossibleMove.getCol() = priorityMoves.at(i).at(1);
            	AiPossibleMove.setVal('X');
            	AiPossibleMove.setHit(true);
		std::cout << "in here breaking before setship 2" << std::endl;
            	AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
            	AiPossibleMove.make(getBoard()); 
		std::cout << "Next ship piece row,col: " << AiPossibleMove.getRow() << " , " << AiPossibleMove.getCol() << std::endl;
	        destroyDir = i;	
		std::cout << "DestroyDir Value: " << destroyDir << std::endl;
		priorityMoves.erase(priorityMoves.begin() + 1,priorityMoves.begin() + priorityMoves.size());
		std::cout << "PriorityMoves size after deleting" << priorityMoves.size() << std::endl;
		setNewPrioMoves(destroyDir, pair);
		return AiPossibleMove; 
	    }else if(board.getFiringBoard().at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()) == board.getBlankChar()){
	        AiPossibleMove.setVal('O');
	        AiPossibleMove.setHit(false);
	        AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));	
		AiPossibleMove.make(getBoard());
		return AiPossibleMove;
		//priorityMoves.erase(priorityMoves.erase(priorityMoves.begin() + i);
	    }
            //gets the element at the first tuple, from the vector of tuples of the priority hits...
        }
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
    if(pair.at(0) - 1 >= 0){
	 setPrioMoves(row - 1, col);
    } 
    //right
    if(pair.at(1) + 1 <= getBoard().getNumCols() - 1){
    	setPrioMoves(row, col + 1);
    } 
    //bottom
    if(pair.at(0) + 1 <= getBoard().getNumRows() - 1){
    	setPrioMoves(row + 1, col);
    }
}
bool BattleShip::HuntDestroyAiPlayer::setNewPrioMoves(const int destroyDir, const std::vector<int> &pair){
    int row = pair.at(0);
    int col = pair.at(1);
    if(destroyDir % 2 == 0){
	while(row - 1 >= 0 && checkHit(row - 1, col)){
	    setBothWayKiller(row,col);
	    row--;
	}
	while(row + 1 <= getBoard().getNumRows() - 1 && checkHit(row + 1, col)){
	    setBothWayKiller(row,col);
	    row++;
	}

    }
    else{	
	//B B B B
	//B X x B B
	//B B B X X
	//col - 2 because i pass in where it randomly hit, and we know there is a piece to left of boat. two pieces total
	while(col - 1 >= 0 && checkHit(row, col - 1)){
	    std::cout << "stuck in here" << std::endl;
	    setBothWayKiller(row,col);
	    col--;
       	    std::cout << "In setBothWay " << col << std::endl;
	}
    	col = pair.at(1);
    	while(col + 1  <= getBoard().getNumCols() - 1 && checkHit(row,col + 1)){
	    setBothWayKiller(row, col);
	    col++;
	}
    }
	
}
void BattleShip::HuntDestroyAiPlayer::setPrioMoves(int row, int col){
    std::vector<int> pair;
    pair.push_back(row);
    pair.push_back(col);
    priorityMoves.push_back(pair);
}	
void BattleShip::HuntDestroyAiPlayer::setBothWayKiller(int row, int col){
   std::vector<int> pair;
   pair.push_back(row); 
   pair.push_back(col);
   killBothWays.push_back(pair);
}
