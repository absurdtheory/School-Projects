all: Langtons_Ant

Langtons_Ant: main.o inputValid.o ant.o menu.o
	g++ main.o inputValid.o ant.o menu.o -o Langtons_Ant

main.o: main.cpp Ant.hpp Menu.hpp Inputvalid.hpp
	g++ -c main.cpp

inputValid.o: inputValid.cpp
	g++ -c inputValid.cpp

ant.o: ant.cpp Ant.hpp
	g++ -c ant.cpp

menu.o: menu.cpp
	g++ -c menu.cpp

clean:
	rm *.o Langtons_Ant
