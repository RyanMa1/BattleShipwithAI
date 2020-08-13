//
// Created by matth on 6/10/2019.
//

#ifndef BATTLESHIP_CHEATINGAIPLAYER_H
#define BATTLESHIP_CHEATINGAIPLAYER_H

#include "AiPlayer.h"

namespace BattleShip {
    class Move;
    class GameAttributes;
    class CheatingAiPlayer : public AiPlayer {
    public:
        void getPossibleMoves() override;

        void setPossibleMoves(int row, int col) override;

    public:
        CheatingAiPlayer(const GameAttributes &gameAttributes);
        Move getMove() ;

    };

}



#endif //BATTLESHIP_CHEATINGAIPLAYER_H
