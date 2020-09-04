//
// Created by matth on 6/10/2019.
//

#ifndef BATTLESHIP_HUNTDESTROYAIPLAYER_H
#define BATTLESHIP_HUNTDESTROYAIPLAYER_H

#include "AiPlayer.h"
namespace BattleShip {
    class Move;
    class GameAttributes;
    class HuntDestroyAiPlayer : public AiPlayer {
    public:
        HuntDestroyAiPlayer(const GameAttributes& gameAttributes);
        void getPossibleMoves() override;
        void setPossibleMoves(int row, int col) override;
        const std::vector<std::vector<int>> &getPriorityMoves() const;
        Move getMove() override;
        void setPriorityMoves(const std::vector<int> &pair);
    private:
        std::vector<std::vector <int>> priorityMoves;
    public:
    };
}
#endif //BATTLESHIP_HUNTDESTROYAIPLAYER_H
