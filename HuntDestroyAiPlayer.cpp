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
    std::cout << "current player turn: " <<playerName << std::endl;
    std::cout << "Num cols: "<< getBoard().getNumCols() << std::endl;
    //there are two vectors, priorityMoves and possibleMoves
    //priorityMoves: Used to check if the bot does hit a boat, then needs to check all around it to find the next part of boat
    std::cout << "In get Move()" << std::endl; 
    std::cout << "Is primoves empty? " << priorityMoves.empty() << std::endl;
//    for(auto x : priorityMoves){
//	std::cout <<"WIthin priority moves are the pair: " <<"row: " << x.at(0) <<"col: "  << x.at(1) << std::endl;
//    }
    for(int x = 0; x < killBothWays.size(); x++){ 
        if(board.getFiringBoard().at(killBothWays.at(x).at(0)).at(killBothWays.at(x).at(1)) != board.getBlankChar()){
            killBothWays.erase(killBothWays.begin() + x); 
  	    std::cout << "erased entire kill Both ways: " << killBothWays.size() << std::endl; 
     }	  
    }
     
    if(!killBothWays.empty()){
	priorityMoves.erase(priorityMoves.begin(), priorityMoves.end());
	std::cout << "in killBothWays.empty" << std::endl;
	std::cout << "size of killBothways size: "<< killBothWays.size()  << std::endl;	

	
	for(int i = 0; i < killBothWays.size(); i++){
	   std::cout << "KillbothWays coordinates: " << "row: "<< killBothWays.at(i).at(0) <<"col: "  << killBothWays.at(i).at(1) << std::endl;
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
        int randomMove = getRandInt(0, possibleMoves.size() - 1, randomNumberGenerator);
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
	    if (checkHit(AiPossibleMove.getRow(), AiPossibleMove.getCol()) ){
//              getShipHealths[AiPossibleMove.getShipHit()] != 0)
//		AiPossibleMove.getRow() = priorityMoves.at(i).at(0);
//            	AiPossibleMove.getCol() = priorityMoves.at(i).at(1);
            	AiPossibleMove.setVal('X');
            	AiPossibleMove.setHit(true);
		std::cout << "in here breaking before setship 2" << std::endl;
            	AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
            	AiPossibleMove.make(getBoard()); 
//		std::cout << "Next ship piece row,col: " << AiPossibleMove.getRow() << " , " << AiPossibleMove.getCol() << std::endl;
	        destroyDir = i;	
		std::cout << "DestroyDir Value: " << destroyDir << std::endl;
		priorityMoves.erase(priorityMoves.begin() + 1,priorityMoves.begin() + priorityMoves.size());
		std::cout << "PriorityMoves size after deleting" << priorityMoves.size() << std::endl;
		//adds new priority moves to vector, removes checking any left over directions
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
    //Add check for pieces that are already been hit next to them ---------------------
    //left
    int row = pair.at(0);
    int col = pair.at(1); 
    if(col - 1 >= 0 && board.getFiringBoard().at(row).at(col - 1) == board.getBlankChar()) {
	setPrioMoves(row, col - 1);
    }
    //top
    if(pair.at(0) - 1 >= 0 && board.getFiringBoard().at(row - 1).at(col) == board.getBlankChar()){
	 setPrioMoves(row - 1, col);
    } 
    //right
    if(pair.at(1) + 1 <= getBoard().getNumCols() - 1 && board.getFiringBoard().at(row).at(col + 1) == board.getBlankChar()){
    	setPrioMoves(row, col + 1);
    } 
    //bottom
    if(pair.at(0) + 1 <= getBoard().getNumRows() - 1 && board.getFiringBoard().at(row + 1).at(col) == board.getBlankChar()){
    	setPrioMoves(row + 1, col);
    }
}
bool BattleShip::HuntDestroyAiPlayer::setNewPrioMoves(const int destroyDir, const std::vector<int> &pair){
    int row = pair.at(0);
    int col = pair.at(1);

//    if(destroyDir % 2 == 0){
	while(row - 1 >= 0 && checkHit(row - 1, col)){
	    setBothWayKiller(row - 1,col);
	    row--;
	}
	std::cout << "row was changed to: " << row << std::endl;
        std::cout << "col was changed to: " << col  << std::endl;
	row = pair.at(0);

	std::cout << "reset row to the orginal value: " << row << std::endl;
	while(row + 1 <= getBoard().getNumRows() - 1 && checkHit(row + 1, col)){
	    std::cout << "getting top of the ship" << std::endl;  
	    setBothWayKiller(row + 1,col);
	    row++;
	}

//   }
//    else{	
	//B B B B
	//B X x B B
	//B B B X X
	//col - 2 because i pass in where it randomly hit, and we know there is a piece to left of boat. two pieces total
	std::cout << "row was changed to: " << row << std::endl;
        std::cout << "col was changed to: " << col  << std::endl;
	col = pair.at(0);
	while(col - 1 >= 0 && checkHit(row, col - 1)){
	    std::cout << "stuck in here" << std::endl;
	    setBothWayKiller(row,col - 1);
	    col--;
       	    std::cout << "In setBothWay " << col << std::endl;
	}
    	col = pair.at(1);
    	while(col + 1  <= getBoard().getNumCols() - 1 && checkHit(row,col + 1)){
	    std::cout << "getting other side of ship" << std::endl; 
	    setBothWayKiller(row, col + 1);
	    col++;
	}
//    }
	
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
