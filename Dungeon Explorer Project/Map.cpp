/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: Map class functions.
*****************************************************************************/
#include "Map.hpp"
#include <iomanip>

/****************************************************************************
**Constructor to create dungeon layout/allocate memory. Intialize pointer to 
**player.
****************************************************************************/
Map::Map(Player *p)
{
	
	//create spaces

	start = playerLocation = new BlankSpace(p);		//blank

	start->top = new ItemSpace(p);					//item
	
	start->top->bottom = start;
	
	placeholder = start->top->top = new TrapSpace(p); //trap
	placeholder->bottom = start->top;

	placeholder->left = new KeySpace(p);				//key
	placeholder->left->right = placeholder;

	placeholder->right = new TrapSpace(p);				//trap
	placeholder->right->left = placeholder;

	placeholder->top = new ItemSpace(p);				//item
	placeholder->top->bottom = placeholder;

	placeholder->top->top = new BlankSpace(p);			//blank
	placeholder->top->top->bottom = placeholder->top;

	placeholder->top->top->top = new TrapSpace(p);		//trap
	placeholder->top->top->top->bottom = placeholder->top->top;

	end = placeholder->top->top->left = new EndSpace(p);	//exit
	end->right = placeholder->top->top->left->right = placeholder->top->top;
	 
	user = p;
}

/***************************************************************************************
**Returns true if player's move was successful, otherwise returns false. Also checks if
**player leaves a TrapSpace without deactivating the trap. If so, the trap triggers and 
**the player takes damage.
****************************************************************************************/
bool Map::movePlayer(int d)	
{
	
	if (playerLocation->getTrapSpace() == true)
	{
		cout << "While leaving the room you triggered the trap!" << endl;
		cout << "You took 5 points of damage." << endl;
		user->subHP(5);
		playerLocation->setTrapSpace(false);
	}
	
	if (d == 1 && playerLocation->top != NULL)
	{
		playerLocation = playerLocation->top;
		return true;
	}
	else if (d == 2 && playerLocation->bottom != NULL)
	{
		playerLocation = playerLocation->bottom;
		return true;
	}
	else if (d == 4 && playerLocation->left != NULL)
	{
		playerLocation = playerLocation->left;
		return true;
	}
	else if (d == 3 && playerLocation->right != NULL)
	{
		playerLocation = playerLocation->right;
		return true;
	}
	else
	{
		cout << "You cannot go that way. Pick another direction." << endl;
		return false;
	}
}


/***************************************************************************************
**Returns a pointer to the player's location
****************************************************************************************/
Space *Map::getPlayer()
{
	return playerLocation;
}


/****************************************************************************************
**Destructor to deallocate memory
*****************************************************************************************/
Map::~Map()	
{
	//cout << "map destructor" << endl;

	if (end != NULL)
	{
		//cout <<"end is not null"<<endl;
		temp = end->right;
		delete end;

		end = temp->top;
		delete end;

		end = temp;
		temp = temp->bottom;
		delete end;

		end = temp;
		temp = temp->bottom;
		delete end;

		end = temp->left;

		delete end;

		end = temp->right;
		delete end;

		end = temp;
		temp = temp->bottom;
		delete end;

		end = temp;
		temp = temp->bottom;
		delete end;

		end = temp;
		delete end;
		
	}
	else
	{
		//cout << "end is null" << endl;
	}
	
}