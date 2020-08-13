CC=g++
DEV=-Wall -g -std=c++14
OPT=-O3 -std=c++14

# JSON=json.hpp
#all: consistentresultverification sortedverification timealgorithms

#consistentresultverification: consistentresultverification.cxx Data.o
#	g++ -std=c++14 consistentresultverification.cxx Data.o -o consistentresultverification

#sortedverification: sortedverification.cxx Data.o
#	g++ -std=c++14 sortedverification.cxx Data.o -o sortedverification

#timealgorithms: timealgorithms.cxx insertionsort.o mergesort.o quicksort.o Data.o
#	g++ -std=c++14 timealgorithms.cxx insertionsort.o mergesort.o quicksort.o Data.o -o timealgorithms
main: main.cpp Config.o Board.o HumanPlayer.o AiPlayer.o BattleShip.o ShipPlacement.o CheatingAiPlayer.o GameAttributes.o Player.o \
RandomAiPlayer.o Utility.o HuntDestroyAiPlayer.o Move.o
	g++ -std=c++14 main.cpp Config.o Board.o HumanPlayer.o HuntDestroyAiPlayer.o AiPlayer.o BattleShip.o ShipPlacement.o CheatingAiPlayer.o GameAttributes.o Player.o \
RandomAiPlayer.o Utility.o Move.o -o main
Config.o: Config.cpp Config.h 
	g++ -std=c++14 -c Config.cpp

Board.o: Board.cpp Board.h ShipPlacement.h Move.h
	g++ -std=c++14 -c Board.cpp

HumanPlayer.o: HumanPlayer.cpp HumanPlayer.h Move.h
	g++ -std=c++14 -c HumanPlayer.cpp

AiPlayer.o: AiPlayer.cpp AiPlayer.h Move.h Utility.h ShipPlacement.h
	g++ -std=c++14 -c AiPlayer.cpp
BattleShip.o: BattleShip.cpp BattleShip.h Move.h Board.h AiPlayer.h HumanPlayer.h CheatingAiPlayer.h RandomAiPlayer.h HuntDestroyAiPlayer.h
	g++ -std=c++14 -c BattleShip.cpp
ShipPlacement.o: ShipPlacement.cpp ShipPlacement.h
	g++ -std=c++14 -c ShipPlacement.cpp
CheatingAiPlayer.o: CheatingAiPlayer.cpp CheatingAiPlayer.h Move.h
	g++ -std=c++14 -c CheatingAiPlayer.cpp
GameAttributes.o: GameAttributes.cpp GameAttributes.h
	g++ -std=c++14 -c GameAttributes.cpp
Player.o: Player.cpp Player.h Board.h GameAttributes.h
	g++ -std=c++14 -c Player.cpp
RandomAiPlayer.o: RandomAiPlayer.cpp RandomAiPlayer.h Move.h
	g++ -std=c++14 -c RandomAiPlayer.cpp
HuntDestroyAiPlayer.o: HuntDestroyAiPlayer.cpp HuntDestroyAiPlayer.h Utility.h Move.h
	g++ -std=c++14 -c HuntDestroyAiPlayer.cpp

Utility.o: Utility.cpp Utility.h
	g++ -std=c++14 -c Utility.cpp
Move.o: Move.cpp Move.h Board.h
	g++ -std=c++14 -c Move.cpp

clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f main
# 	rm -f sortedverification
# 	rm -f timealgorithms