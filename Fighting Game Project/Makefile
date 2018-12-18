all: Final_Project

Final_Project: main.o Game.o Map.o Space.o BlankSpace.o  TrapSpace.o EndSpace.o  KeySpace.o ItemSpace.o Item.o Player.o inputValid.o
	g++ -g main.o Game.o Map.o Space.o BlankSpace.o  TrapSpace.o EndSpace.o KeySpace.o ItemSpace.o Item.o Player.o inputValid.o -o Final_Project

main.o: main.cpp Game.hpp
	g++ -std=c++11 -c main.cpp

Game.o: Game.cpp Game.hpp
	g++ -std=c++11 -c Game.cpp

Map.o: Map.cpp Map.hpp
	g++ -std=c++11 -c Map.cpp

Space.o: Space.cpp Space.hpp
	g++ -std=c++11 -c Space.cpp

BlankSpace.o: BlankSpace.cpp BlankSpace.hpp
	g++ -std=c++11 -c BlankSpace.cpp

TrapSpace.o: TrapSpace.cpp TrapSpace.hpp
	g++ -std=c++11 -c TrapSpace.cpp

EndSpace.o: EndSpace.cpp EndSpace.hpp
	g++ -std=c++11 -c EndSpace.cpp

KeySpace.o: KeySpace.cpp KeySpace.hpp
	g++ -std=c++11 -c KeySpace.cpp

ItemSpace.o: ItemSpace.cpp ItemSpace.hpp
	g++ -std=c++11 -c ItemSpace.cpp

Item.o: Item.cpp Item.hpp
	g++ -std=c++11 -c Item.cpp

Player.o: Player.cpp Player.hpp
	g++ -std=c++11 -c Player.cpp

inputValid.o: inputValid.cpp
	g++ -c inputValid.cpp

clean:
	rm *.o Final_Project
