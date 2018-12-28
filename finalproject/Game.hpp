/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: Header for Game class
*****************************************************************************/
#ifndef GAME_HPP
#define GAME_HPP
#include "Map.hpp"
#include "Player.hpp"
#include "Inputvalid.hpp"
using std::cin;

class Game
{
private:
	Map	*gameMap;
	Player *player1;

public:
	Game();				//allocates gameMap and player1 pointers
	void Menu();		//calls the menu
	~Game();			//deallocated gameMap and player1 pointers
};

#endif