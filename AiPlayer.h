//
// Created by matth on 6/9/2019.
//

#ifndef BATTLESHIP_AIPLAYER_H
#define BATTLESHIP_AIPLAYER_H
#include <random>
#include "Player.h"

namespace BattleShip {
    class Move;
    class GameAttributes;
    class AiPlayer : public Player {
    public:
        explicit AiPlayer(const GameAttributes &gameAttributes);

        static void seed_random_number_generator(int seed);

        void placeShips() override;

        void setName() override;

        virtual Move getMove() = 0;
        virtual void getPossibleMoves() = 0;

        virtual void setPossibleMoves(int row, int col) = 0;

        void getFiringBoard() override;

        void getPlacementBoard() override;

    protected:
        static std::mt19937 randomNumberGenerator;
        std::vector<std::vector<int>> possibleMoves;

    private:
        static int nextAiId;
        const int aiId;
    };
}
#endif //BATTLESHIP_AIPLAYER_H
