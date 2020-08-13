//
// Created by matth on 6/9/2019.
//

#ifndef BATTLESHIP_BATTLESHIP_H
#define BATTLESHIP_BATTLESHIP_H
#include <memory>
#include "GameAttributes.h"
#include "Move.h"
#include "Board.h"

namespace BattleShip {
    class Player;
    class Move;
    class BattleShip {
    public:
        explicit BattleShip(const std::vector<std::string> &file);
        virtual ~ BattleShip() = default;
        void play();

    private:
        void typeOfGame();
        void determineStartingPlayer();
        Move getCurrentPlayerMove();
        Player& getCurrentPlayer();
        bool gameWon();
        void changeTurn();
        void declareResults() const;
        void addPlayersToGame(int numPlayers);
        void getAiType(int &aiType);
        void setAi();
        Board& getOtherPlayersBoard(int player);
        void getBoards();
        void updateBoards(Move& move);
        Player& getOtherPlayer();

    private:
        std::vector<std::unique_ptr<Player>> players;
        std::vector<Board> playerBoard;
        int playerTurn;
        GameAttributes gameAttributes;


    };
}


#endif //BATTLESHIP_BATTLESHIP_H
