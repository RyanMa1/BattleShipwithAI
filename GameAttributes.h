//
// Created by matth on 6/9/2019.
//

#ifndef BATTLESHIP_GAMEATTRIBUTES_H
#define BATTLESHIP_GAMEATTRIBUTES_H
#include <iostream>
#include <map>



namespace BattleShip {
    class GameAttributes {
    public:

        GameAttributes(const std::vector<std::string> &gameFile);
        void getShipAttributes(const std::vector<std::string> &gameFile);
        int getSize() const;
        int getRowSize() const;
        int getColSize() const;
        int getNumBoats() const;

        const std::map<char, int> &getShipAttributes() const;
        std::map<char, int> shipAttributes;
        std::vector<std::string> gameAttributes;
        int rowSize, colSize, numBoats;

    };
}


#endif //BATTLESHIP_GAMEATTRIBUTES_H
