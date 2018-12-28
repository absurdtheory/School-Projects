/****************************************************************************
**Program Name: Program 1
**Author: Alexis Tucker
**Date: 1/17/2018
**Description: Menu function that allows the user to either start the program
** or quit. It contains it's own input validation. It returns the user's choice
** to main.
******************************************************************************/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;


int menuSelect()
{
	int choice;

	//display menu
	
	cout << "Langton's Ant Simulation Menu\n"
		<< "1. Start Langton's Ant Simulation\n"
		<< "2. Quit\n"
		<< "Please enter your choice: ";

	cin >> choice;

	//test for correct input
	while (cin.fail() || (choice != 1 && choice != 2))
	{
		cout << "Please enter 1 or 2. Re-enter your choice ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> choice;
	}

	return choice;

}