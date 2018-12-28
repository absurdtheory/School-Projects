/****************************************************************************
**Program Name: Project 1
**Author: Alexis Tucker
**Date: 1/17/2018
**Description: Prompts the user to enter numbers and sends them to inputValid.
**If ever number is valid, it creates an ant object, moves the ant, and displays
** the screen. Repeats until the user chooses to quit in the menu function.
******************************************************************************/
#include <iostream>
#include "Ant.hpp"
#include "Inputvalid.hpp"
#include "Menu.hpp"
using std::cout;
using std::cin;
using std::endl;

//int menuSelect();
bool inputValid(int c);



main()
{
	
	int selection = menuSelect(),		//calls menu function and assigns returned value to selection
		numRows,						//number of rows on board	
		numCols,						//number of columns on board
		numSteps,						//number of steps ant should take
		startRow,						//ant's starting row
		startCol,						//ant's starting column
		startOrient;					//the direction the ant is facing initially
	Orient sOrient;						//the direction the ant is facing initially in enum
	

	while (selection != 2)				//while the user does not quit
	{

		//prompt for rows
		cout << "Enter the number of rows for the board: ";
		
		cin >> numRows;

		//validate input
		while (inputValid(numRows) != true)
		{
			cin >> numRows;
		}


		//prompt for columns
		cout << "Enter the number of columns for the board: ";

		cin >> numCols;

		//validate input
		while (inputValid(numCols) != true)
		{
			cin >> numCols;
		}


		//prompt for steps
		cout << "Enter the number of steps for the ant to take: ";

		cin >> numSteps;

		//validate input
		while (inputValid(numSteps) != true)
		{
			cin >> numSteps;
		}


		//prompt for ant's starting row
		cout << "Enter the ant's starting row: ";
		cin >> startRow;
		 
		//validate input, check if starting row is within total number of rows
		while (inputValid(startRow) != true || startRow > numRows)
		{ 
			cout << " Please enter a number less than or equal to the number of rows: ";
			cin >> startRow;
		}


		//prompt for ant's starting column
		cout << "Enter the ant's starting column: ";
		cin >> startCol;

		//validate input and check if starting column is within total number of columns
		while (inputValid(startCol) != true || startCol > numCols)
		{
			cout << " Please enter a number less than or equal to the number of rows: ";
			cin >> startCol;
		}


		//prompt direction ant is facing
		cout << "Enter the direction the ant is facing:\n"
			<< "1. Up\n"
			<< "2. Down\n"
			<< "3. Left\n"
			<< "4. Right\n";

		cin >> startOrient;
		
		//validate input and check if selection is within options
		while (inputValid(numSteps) != true || startOrient > 4)
		{
			cout << "Please enter 1 through 4: ";
			cin >> startOrient;
		}


		//assign user selection to enum
		if (startOrient != 2 & startOrient !=3 & startOrient !=4)
		{
			sOrient = UP;
		}
		else if (startOrient != 1 & startOrient != 3 & startOrient != 4)
		{
			sOrient = DOWN;
		}
		else if (startOrient != 1 & startOrient != 2 & startOrient != 4)
		{
			sOrient = LEFT;
		}
		else
		{
			sOrient = RIGHT;
		}
		

		//create object of ant class
		Ant ant1(numRows, numCols, startRow, startCol, sOrient);

		//display starting point of ant
		ant1.printBoard();

		//display moves
		for (int i = 0; i < numSteps; i++)
		{
			ant1.moveAnt();
			ant1.printBoard();
		}

		//end simulation, return to menu
		cout << "Simulation ended. Returning to Menu." << endl;
		selection = menuSelect();
	}

	cout << "Good-bye." << endl;
	return 0;
}