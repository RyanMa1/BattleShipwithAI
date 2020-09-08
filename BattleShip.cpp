//
// Created by matth on 6/9/2019.
//

#include <iostream>
#include <memory>
#include <sstream>
#include <vector>
#include "BattleShip.h"
#include "Move.h"
#include "Board.h"
#include "AiPlayer.h"
#include "HumanPlayer.h"
#include "CheatingAiPlayer.h"
#include "RandomAiPlayer.h"
#include "HuntDestroyAiPlayer.h"



BattleShip::BattleShip::BattleShip(const std::vector<std::string> &file) :
        playerTurn(-1), gameAttributes(file)
{
    typeOfGame();
}

void BattleShip::BattleShip::typeOfGame() {

    const int hVSh = 1, hVSai = 2, aiVSai = 3;
    int gameType;
    std::cout << "What type of game do you want to play?" << std::endl;
    std::cout << "1. Human vs Human" << std::endl;
    std::cout << "2. Human vs AI" << std::endl;
    std::cout << "3. AI vs AI" << std::endl;
    std::cout << "Your choice: ";
//    gameType = getLineFunction();
    std::string choice;
    std::getline(std::cin, choice);
    std::stringstream userIn(choice);
    userIn >> gameType;

    if (gameType == hVSh) {
        std::cout << "Player 1 ";
        players.push_back(std::make_unique<HumanPlayer>(gameAttributes));
        std::cout << "Player 2 ";
        players.push_back(std::make_unique<HumanPlayer>(gameAttributes));
    }
    else if (gameType == hVSai){
        std::cout << "Player 1 ";
        players.push_back(std::make_unique<HumanPlayer>(gameAttributes));
        setAi();
    }else if (gameType == aiVSai){
        setAi();
        setAi();
    }

}

void BattleShip::BattleShip::getAiType(int &aiType) {
    std::cout << "What AI do you want?" << std::endl;
    std::cout << "1. Cheating AI" << std::endl;
    std::cout << "2. Random AI" << std::endl;
    std::cout << "3. Hunt Destroy AI" << std::endl;
    std::cout << "Your choice: ";
    std::string choice;
    std::getline(std::cin, choice);
    std::stringstream userIn(choice);
    userIn >> aiType;

}

void BattleShip::BattleShip::play() {
    determineStartingPlayer();
    //get both player boards
    //make Move
    getBoards();
    while(true){
        //display firing board & placement board
        std::cout << getCurrentPlayer().getName() << "'s Firing Board" << std::endl;
        getCurrentPlayer().getBoard().displayFiringBoard();
        std::cout << "\n";
        htd::cout << "\n";
        std::cout << getCurrentPlayer().getName() << "'s Placement Board" << std::endl;
        getCurrentPlayer().getBoard().displayShipPlacement();

        //get the move, returns hlayermove
	std::cout << "breaks before here" << std::endl;
        Move move = getCurrentPlayerMove();

        //after firing display updated boards
        std::cout << getCurrentPlayer().getName() << "'s Firing Board" << std::endl;
        getCurrentPlayer().getBoard().displayFiringBoard();
        std::cout << "\n";
        std::cout << "\n";
        std::cout << getCurrentPlayer().getName() << "'s Placement Board" << std::endl;
        getCurrentPlayer().getBoard().displayShipPlacement();
        updateBoards(move);
        //display firing boards & placement boards
        std::cout << getCurrentPlayer().getShipHealths().empty() << std::endl;
        //display who won
        if(gameWon()){
            std::cout << getCurrentPlayer().getName() << " won the game!" << std::endl;
            break;
        }
        changeTurn();

    }



}

void BattleShip::BattleShip::setAi() {
    int aiType;
    getAiType(aiType);
    const int cheatingAi = 1, randomAi = 2, huntDestroyAi = 3;
    if(aiType == cheatingAi){
        players.push_back(std::make_unique<CheatingAiPlayer>(gameAttributes));
    }else if(aiType == randomAi){
        players.push_back(std::make_unique<RandomAiPlayer>(gameAttributes));
    }else if(aiType == huntDestroyAi){
        players.push_back(std::make_unique<HuntDestroyAiPlayer>(gameAttributes));
    }
}

void BattleShip::BattleShip::changeTurn() {
    playerTurn = (playerTurn + 1) % players.size();
}

void BattleShip::BattleShip::determineStartingPlayer() {
    playerTurn = 0;
}

BattleShip::Board& BattleShip::BattleShip::getOtherPlayersBoard(int player) {
    return (*(players.at(player))).getBoard();
}

void BattleShip::BattleShip::getBoards() {
    (*(players.at(0))).clearOpponentBoard();
    (*(players.at(1))).clearOpponentBoard();
    (*(players.at(0))).setOpponentBoard(getOtherPlayersBoard(1));
    (*(players.at(1))).setOpponentBoard(getOtherPlayersBoard(0));

}


BattleShip::Move BattleShip::BattleShip::getCurrentPlayerMove() {
    return getCurrentPlayer().getMove();
}

BattleShip::Player &BattleShip::BattleShip::getCurrentPlayer() {
    return *(players.at(playerTurn));
}

void BattleShip::BattleShip::updateBoards(Move& move) {
    getOtherPlayer().getBoard().updatePlacementBoard(move);

    if(move.isHit()){
        //add to the hunt/destroy's Ai priority hits
        std::cout << getCurrentPlayer().getName() << " hit " << getOtherPlayer().getName() << "'s " << move.getShipHit() << "!" << std::endl;
        getOtherPlayer().updateShipHealth(move.getShipHit(), getCurrentPlayer().getName(), getOtherPlayer().getName());
    }else{
        std::cout << "Missed.\n" <<  std::endl;
    }

}

bool BattleShip::BattleShip::gameWon()  {
    //we need to check in our shiphealth map,
    return (getOtherPlayer().getShipHealths().empty());
}

BattleShip::Player &BattleShip::BattleShip::getOtherPlayer() {
    return (*players.at((playerTurn + 1) % players.size()));
}





