/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: Functions for item class.
*****************************************************************************/
#include "Item.hpp"

/***************************************************************************************
**Takes a string and sets the item name
****************************************************************************************/
void Item::setItemName(string n)
{
	itemName = n;
}


/***************************************************************************************
**Returns the item name as a string
****************************************************************************************/
string Item::getItemName()
{
	return itemName;
}


/***************************************************************************************
**Takes a string and sets the item description
****************************************************************************************/
void Item::setDesc(string n)
{
	itemDesc = n;
}


/***************************************************************************************
**Returns the item description
****************************************************************************************/
string Item::getDesc()
{
	return itemDesc;
}

/***************************************************************************************
**Returns true if item is an exit key
****************************************************************************************/
bool Item::isKey()
{
	
	if (exitKey == true)
	{
		return true;
	}
	else
	{
		return false;
	}

}

/***************************************************************************************
**Takes a bool and sets an item to exit key
****************************************************************************************/
void Item::setExitKey(bool n)
{
	exitKey = n;
}