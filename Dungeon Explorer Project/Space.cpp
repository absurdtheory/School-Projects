/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: Functions for Space class
*****************************************************************************/
#include "Space.hpp"

/***************************************************************************************
**Returns spaceDesc
****************************************************************************************/
string Space::getSpaceDesc()
{
	return spaceDesc;
}


/***************************************************************************************
**Returns true if the exit door is open
****************************************************************************************/
bool Space::getOpenDoor()
{
	if (openDoor == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/***************************************************************************************
**Returns true is derived class is a TrapSpace that is armed. Otherwise, returns false.
****************************************************************************************/
bool Space::getTrapSpace()
{
	return trapSpace;
}


/***************************************************************************************
**Allows trapSpace to change to false once a trap is activated.
****************************************************************************************/
void Space::setTrapSpace(bool b)
{
	trapSpace = b;
}

Space::~Space()
{
	//cout << "space destructor" << endl;
}
