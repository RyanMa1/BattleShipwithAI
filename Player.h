//
// Created by matth on 6/9/2019.
//

#ifndef BATTLESHIP_PLAYER_H
#define BATTLESHIP_PLAYER_H
#include <iostream>
#include <map>
#include "Board.h"

namespace BattleShip{
    class Move;
    class GameAttributes;
    class Player {
    public:
        //constructor, every player has a name and a board attached to them
        Player(const GameAttributes &gameAttributes);
        virtual ~Player() = default;
        //void setUp(const GameAttributes& gameAttributes);
        virtual void placeShips() = 0;
        virtual void setName() = 0;
        void initializeName(const std::string &name);
        const std::string& getName() const;
        //Pure virtual method, makes our class abstract, since the get move is different for each type of player
        virtual Move getMove() = 0;
        Board& getBoard();
        void setOpponentBoard(Board& board);
        void clearOpponentBoard();
        bool checkHit(const int &row, const int &col);
        void updateShipHealth(char val, std::string playersName1, std::string playersName2);
        const std::map<char, int> &getShipHealths() const;
        virtual void getFiringBoard() = 0;
        virtual void getPlacementBoard() = 0;


    protected:
        std::string playerName;
        Board board;
        std::vector<std::string> opponentBoard;
        std::map<char, int> shipHealths;
    };


}


#endif //BATTLESHIP_PLAYER_H
