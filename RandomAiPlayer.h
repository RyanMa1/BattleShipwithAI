//
// Created by matth on 6/10/2019.
//

#ifndef BATTLESHIP_RANDOMAIPLAYER_H
#define BATTLESHIP_RANDOMAIPLAYER_H

#include "AiPlayer.h"
#include "Utility.h"

namespace BattleShip{
    class Move;
    class GameAttributes;
    class RandomAiPlayer : public AiPlayer {
        void getPossibleMoves() override;
        void setPossibleMoves(int row, int col) override;

    public:
        Move getMove() ;

    public:
        RandomAiPlayer(const GameAttributes& gameAttributes);
    };
}


#endif //BATTLESHIP_RANDOMAIPLAYER_H
