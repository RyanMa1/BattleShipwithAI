//
// Created by matth on 6/9/2019.
//

#ifndef BATTLESHIP_HUMANPLAYER_H
#define BATTLESHIP_HUMANPLAYER_H

#include "Player.h"

namespace BattleShip {
    class Move;
    class GameAttributes;
    class HumanPlayer : public Player {
    public:
        HumanPlayer(const GameAttributes &gameAttributes);

        void placeShips() override;
        void getFiringBoard() override ;
        void getPlacementBoard() override ;
        Move getMove() override;

        void setName() override;

        char checkPlacementStyle();


    protected:

        //virtual Move parseInput();
    private:
        char placementStyle;
        std::string userInput;

    };
}


#endif //BATTLESHIP_HUMANPLAYER_H
