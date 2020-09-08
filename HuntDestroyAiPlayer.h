//
// Created by matth on 6/10/2019.
//

#ifndef BATTLESHIP_HUNTDESTROYAIPLAYER_H
#define BATTLESHIP_HUNTDESTROYAIPLAYER_H

#include "AiPlayer.h"
#include <deque>
#include <unordered_map>
namespace BattleShip {
    class Move;
    class GameAttributes;
    class HuntDestroyAiPlayer : public AiPlayer {
    public:
        HuntDestroyAiPlayer(const GameAttributes& gameAttributes);
        void getPossibleMoves() override;
	void setPrioMoves(int row, int col);
        void setPossibleMoves(int row, int col) override;
        const std::deque<std::vector<int>> &getPriorityMoves() const;
        Move getMove() override;
        void setPriorityMoves(const std::vector<int> &pair);
    private:
        std::deque<std::vector <int>> priorityMoves;
    public:
    };
}
#endif //BATTLESHIP_HUNTDESTROYAIPLAYER_H
