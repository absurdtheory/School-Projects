/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: Main function, calls srand. Creates a game object and calls the
**menu.
*****************************************************************************/
#include "Game.hpp"
#include <ctime>
#include <cstdlib>


int main()
{
	srand(time(0));

	Game game1;

	game1.Menu();

	return 0;
}