/***********************************************************************
**Program Name: Lab3
**Author: Alexis Tucker
**Date: 
**Description: inputValid function that tests if the user input is 
** an integer and if that integer is greater than zero. If both tests
**pass the function returns true. If either test fails, it returns false.
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
	/*
	//test if the integer is greater than zero
	else if (c <= 0)
	{
		return false;
	}
	*/

	else
	{
		return true;
	}
}
	