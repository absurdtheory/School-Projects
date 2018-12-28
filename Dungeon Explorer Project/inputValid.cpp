/***********************************************************************
**Program Name: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: inputValid function that tests if the user input is 
**an integer. If it passes the test it returns true, otherwise
**it returns false.
************************************************************************/
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

bool inputValid(int c)
{

	//test if input is an integer
	if(cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		return false;
	}

	else
	{
		return true;
	}
}
	