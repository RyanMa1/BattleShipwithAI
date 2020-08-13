//
// Created by matth on 6/9/2019.
//

#ifndef BATTLESHIP_MOVE_H
#define BATTLESHIP_MOVE_H
#include <sstream>
#include <vector>
#include <tuple>

namespace BattleShip {
    class Player;
    class Board;

    class Move {
    public:
        bool isHit() const;

        void setHit(bool hit);

        Move(const Player& maker);
        Move(const Player& maker, int row, int col);
        bool isValid(const Board& board) const;
        void make(BattleShip::Board &board);

        int& getRow();
        int& getCol();

        void setVal(char value);

        void setShipHit(char charHit);

        char getShipHit() const;

        char getVal() const;

        std::vector<std::tuple<int, int>> &getPriorityHits4Ai();

    private:
        const Player& maker;
        int row, col;
        char val, shipHit;
        bool hit;
        std::vector<std::tuple<int,int>> priorityHits4Ai;
    };
}


#endif //BATTLESHIP_MOVE_H
