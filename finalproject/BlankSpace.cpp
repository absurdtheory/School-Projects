/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: An empty room with nothing to interact with. Generates a 
**room description randomly.
*****************************************************************************/
#include "BlankSpace.hpp"


/***************************************************************************************
**Constructor that initializes variables, takes a pointer to the player
**Randomly chooses a room description.
****************************************************************************************/
BlankSpace::BlankSpace(Player *p)
{
	//generate a number 1-4 and assign spaceDesc based on that number to add variety
	int genDesc = (rand() % 4 + 1);

	if (genDesc == 1)
	{
		spaceDesc = "The room is empty besides cobwebs, dust,\nand what appears to be old bloodstains on the walls.";
	}
	else if (genDesc == 2)
	{
		spaceDesc = "The only thing in this room is you, the poison air,\nand the condensation of your breath in the cold.";
	}
	else if (genDesc == 3)
	{
		spaceDesc = "There's nothing to see here. Might as well keep moving.";
	}
	else
	{
		spaceDesc = "The room is totally empty, you can hear your breath echo \nagainst the stone-clad walls.";
	}
}

/***************************************************************************************
**Displays which ways player can move and room
****************************************************************************************/
void BlankSpace::investigate()
{
	cout << endl;

	if (this->left != NULL)
	{
		cout << "There is a room to the West." << endl;
	}
	if (this->right != NULL)
	{
		cout << "There is a room to the East." << endl;
	}
	if (this->top != NULL)
	{
		cout << "There is a room to the North." << endl;
	}
	if (this->bottom != NULL)
	{
		cout << "There is a room to the South." << endl;
	}
	cout << endl;
	
	cout << "There's nothing to do but continue onward." << endl;
}


/***************************************************************************************
**If the player tried to use an item on this room, nothing happens
****************************************************************************************/
void BlankSpace::interact(Item n)
{
	cout << "There is nothing to use an item on here." << endl;
}