//
// Created by matth on 6/9/2019.
//

#ifndef BATTLESHIP_CONFIG_H
#define BATTLESHIP_CONFIG_H
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

namespace BattleShip {
    std::vector<std::string> configGame(const std::string &filename);
    std::vector<std::string> readfile(const std::string& filename);

}


#endif //BATTLESHIP_CONFIG_H
