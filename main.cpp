#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Config.h"
#include "BattleShip.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "AiPlayer.h"

int main(int argc, char **argv) {
    std::string filename(argv[1]);
    if(argc > 2) {
        BattleShip::AiPlayer::seed_random_number_generator(std::stoi(argv[2]));
    }

    std::vector<std::string> gameConfig;
    gameConfig = BattleShip::configGame(filename);
    BattleShip::BattleShip BattleShipStart(gameConfig);
    BattleShipStart.play();
    


    return 0;
}