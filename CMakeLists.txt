cmake_minimum_required(VERSION 3.13)
project(BattleShip)

set(CMAKE_CXX_STANDARD 14)

add_executable(BattleShip main.cpp BattleShip.cpp BattleShip.h GameAttributes.cpp GameAttributes.h Player.cpp Player.h Board.cpp Board.h ShipPlacement.cpp ShipPlacement.h AiPlayer.cpp AiPlayer.h Utility.cpp Utility.h HumanPlayer.cpp HumanPlayer.h Move.cpp Move.h Config.cpp Config.h CheatingAiPlayer.cpp CheatingAiPlayer.h RandomAiPlayer.cpp RandomAiPlayer.h HuntDestroyAiPlayer.cpp HuntDestroyAiPlayer.h)