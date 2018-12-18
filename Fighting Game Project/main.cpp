/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Main function. Creates Game object and calls it's menu function.
*********************************************************************************/
#include "Game.hpp"
#include <ctime>

int main()
{
	Game game1;
	int select;
	srand(time(0));

	cout << "Welcome to Fantasy Combat!" << endl;


	game1.Menu();

	
	cout << endl;
	cout << "Goodbye!" << endl;
	
	return 0;

}