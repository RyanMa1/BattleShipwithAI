//
// Created by matth on 6/9/2019.
//

#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H
#include <vector>
#include <string>
#include "ShipPlacement.h"

namespace BattleShip{
    class Move;
    class Board {
    public:
        explicit Board(const int &rowSize, const int &columnSize);
        Board() = default;
        int getNumRows() const;
        int getNumCols() const;
        bool canPlaceShipAt(ShipPlacement &shipPlacement);
        bool overlap(ShipPlacement &shipPlacement);
        void addShip(char symbol, ShipPlacement &shipPlacement);
        bool inBoundsBoatSet(ShipPlacement &shipPlacement);

        std::vector<std::string> &getFiringBoard();

        const std::vector<std::string> &getPlacementBoard() const;

        bool inBoundsFire(const int &row, const int &col) const;
        bool isBetween(const int &row, const int &col, const int &boardSize) const;
        void setBoat(const int &row, const int &col, const int &boatSize, const char &val, const char &orient);
        void setBoatHoriz(const int &row, const int &colStart, const int &shipSize, const char &val);
        void setBoatVert(const int &row, const int &col, const int &shipSize, const char &val);
        void displayFiringBoard() const;
        void displayShipPlacement() const;
        void setFire(const int &row, const int &col, const char &val);
        bool checkHit(const int & row, const int &col);
        const char& at(const int &row, const int& col) const;
        const char getBlankChar() const;
        using iterator = std::vector<std::string>::iterator;
        using const_iterator = std::vector<std::string>::const_iterator;
        iterator begin();
        iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;

        void updatePlacementBoard(Move &move);

    private:
        std::vector<std::string> firingBoard;
        std::vector<std::string> placementBoard;
        const char blankChar = '*';

    };
}


#endif //BATTLESHIP_BOARD_H
