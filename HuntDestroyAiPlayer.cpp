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
    if(priorityMoves.empty()){
       int randomMove = getRandInt(0, possibleMoves.size() - 1, randomNumberGenerator);
       pair = possibleMoves.at(randomMove);
       AiPossibleMove.getRow() = pair.at(0);
       AiPossibleMove.getCol() = pair.at(1);
       possibleMoves.erase(possibleMoves.begin() + randomMove);
       if(checkHit(AiPossibleMove.getRow(), AiPossibleMove.getCol())) {
            priorityMoves.push_back(pair);
	    setPriorityMoves(pair);
	    markHitShip(AiPossibleMove, 'X');
	    return AiPossibleMove;	
        }else{
	    markHitShip(AiPossibleMove, 'O');
	    return AiPossibleMove;
        }
     }else{
	char dir;
	countForBothSidesCheck = false;
	if(countForBothSidesCheck){
		setDirOpposite();
	}	
	pair = priorityMoves.at(1);
	AiPossibleMove.getRow() = pair.at(0);
	AiPossibleMove.getCol() = pair.at(1);
	if(checkHit(AiPossibleMove.getRow(),AiPossibleMove.getCol()){
		dir = getDirection(pair);
		priorityMoves.erase(priorityMoves.begin() + 1, priorityMoves.end());	
		setDestroy(dir, pair);
	}else{
		priorityMoves.erase(priorityMoves.begin() + 1);
		markHitShip(AiPossibleMove, 'O');
	}
 	
    }
}
BattleShip::Move BattleShip::HuntDestroyAiPlayer::setDestroy(char dir, Move& AiPossibleMove){
	switch(dir){
		case('l'):
			if(AiPossibleMove.getCol() - 1 >= 0)		
				AiPossibleMove.getCol()--;
			else{
				countForBothSidesCheck = true;
				setDirOpposite();
			}
			return AiPossibleMove;			
		case('r'):
			AiPossibleMove.getCol()++;
			return AiPossibleMove;
		case('t'):
			AiPossibleMove.getRow()--;
			return AiPossibleMove;
		case('b'):
			AiPossibleMove.getRow()++;
	}
}
char BattleShip::HuntDestroyAiPlayer::getDirection(std::vector<int> pair){
	int row = pair.at(0);
	int col = pair.at(1);
	int crow = priorityMoves.at(0).at(0);
	int ccol = priorityMoves.at(0).at(1);
	if(ccol - 1 == col){
		return 'l';
	}else if(ccol + 1 == col){
		return 'r';
	}else if(crow - 1 == row){
		return 't';
	}else if(crow + 1 == row){
		return 'b';
	}
}
void BattleShip::HuntDestroyAiPlayer::markHitShip(Move& AiPossibleMove, char XorY){
	AiPossibleMove.setVal(XorY);
	switch(XorY){
		case('X'):
			AiPossibleMove.setHit(true);
		case('O'):
			AiPossibleMove.setHit(false);
        AiPossibleMove.setShipHit(opponentBoard.at(AiPossibleMove.getRow()).at(AiPossibleMove.getCol()));
        AiPossibleMove.make(getBoard());
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
