//
// Created by matth on 6/9/2019.
//

#include "HumanPlayer.h"
#include "Move.h"
#include <iostream>
#include <sstream>

BattleShip::HumanPlayer::HumanPlayer(const BattleShip::GameAttributes &gameAttributes) : Player(gameAttributes){
placeShips();

}

BattleShip::Move BattleShip::HumanPlayer::getMove() {
    Move playerMove(*this);
    do {

        std::cout << playerName << ", where would you like to fire?" << std::endl;
        std::cout << "Enter your attack coordinate in the form row col: ";
        std::string line;
        std::getline(std::cin, line);
        std::stringstream userIn(line);
        userIn >> playerMove.getRow() >> playerMove.getCol();
    }while(!playerMove.isValid(board));

    if(checkHit(playerMove.getRow(), playerMove.getCol())){
        playerMove.setVal('X');
        playerMove.setHit(true);
        playerMove.setShipHit(opponentBoard.at(playerMove.getRow()).at(playerMove.getCol()));
        playerMove.make(getBoard());

    }else{
        playerMove.setVal('O');
        playerMove.setHit(false);
        playerMove.setShipHit(opponentBoard.at(playerMove.getRow()).at(playerMove.getCol()));
        playerMove.make(getBoard());
    }
    return playerMove;
}


void BattleShip::HumanPlayer::placeShips() {
    ShipPlacement placement;
    setName();
    for (const auto& ship : shipHealths) {
        //
        placement.shipSize = ship.second;
        do {
            //display board first
            getBoard().displayShipPlacement();
            std::cout << playerName << ", do you want to place " << ship.first << " horizontally or vertically?" << std::endl;
            placementStyle = checkPlacementStyle();
            if (placementStyle == 'h' || placementStyle == 'H') {
                bool parseSuccesfully = true;
                do {
                    placement.orientation = 'h';
                    //ask where to place ships
                    std::cout << playerName <<  ", enter the row and column you want to place " << ship.first << ", which is "
                              << ship.second
                              << " long, at with a space in between row and col: ";
                    std::string line;
                    std::getline(std::cin, line);
                    std::stringstream userIn(line);
                    userIn >> placement.rowStart >> placement.colStart;
                    placement.rowEnd = placement.rowStart;
                    placement.colEnd = placement.colStart + ship.second - 1;
                    parseSuccesfully = parseSuccesfully && static_cast<bool> (userIn);
                    std::string leftovers;
                    userIn >> leftovers;
                    parseSuccesfully = parseSuccesfully && !userIn;
                } while (!parseSuccesfully);
            } else if (placementStyle == 'v' || placementStyle == 'V') {
                bool parseSuccesfully = true;
                do {
                    placement.orientation = 'v';

                    //ask where to place ships
                    std::cout << playerName << ", enter the row and column you want to place " << ship.first << ", which is "
                              << ship.second
                              << " long, at with a space in between row and col: ";
                    std::string line;
                    std::getline(std::cin, line);
                    std::stringstream userIn(line);
                    userIn >> placement.rowStart >> placement.colStart;
                    placement.rowEnd = placement.rowStart + ship.second - 1;
                    placement.colEnd = placement.colStart;
                    parseSuccesfully = parseSuccesfully && static_cast<bool> (userIn);
                    std::string leftovers;
                    userIn >> leftovers;
                    parseSuccesfully = parseSuccesfully && !userIn;
                } while (!parseSuccesfully);

            }
        }while (!getBoard().canPlaceShipAt(placement));
        getBoard().addShip(ship.first, placement);
        }
    getBoard().displayShipPlacement();
}


void BattleShip::HumanPlayer::setName() {
    std::string name;
    std::cout << "please enter your name: ";
    std::string line;
    std::getline(std::cin, line);
    std::stringstream userIn(line);
    userIn >> name;
    initializeName(name);
}
char BattleShip::HumanPlayer::checkPlacementStyle() {
    std::string userInput;


    std::cout << "Enter h for horizontal or v for vertical" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> userInput;
    //dont forget to check input !
    std::string line;
    std::getline(std::cin, line);
    std::stringstream userIn(line);
    userIn >> userInput;
    placementStyle = userInput[0];
    if(userInput.size() > 1 || userInput.empty() || isdigit(userInput[0])){
        return 'm';
    }

    return placementStyle;
}

void BattleShip::HumanPlayer::getPlacementBoard() {
    std::cout << getName() << "'s Placement Board" << std::endl;
    getBoard().displayFiringBoard();
}

void BattleShip::HumanPlayer::getFiringBoard() {
    std::cout << getName() << "'s Firing Board" << std::endl;
    getBoard().displayShipPlacement();
}



