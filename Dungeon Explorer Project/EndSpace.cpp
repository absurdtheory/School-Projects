/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: Functions for end space
*****************************************************************************/
#include "EndSpace.hpp"

/***************************************************************************************
**Constructor that initializes variables, takes a pointer to the player
****************************************************************************************/
EndSpace::EndSpace(Player *p)
{
	openDoor = false;
	user = p;

	spaceDesc = "You see a iron-cast door. Could this be the exit?";
}


/***************************************************************************************
**Investigates the room, shows where adjacent rooms are, displays more information about
**room
****************************************************************************************/
void EndSpace::investigate()
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

	cout << "The door is locked... maybe there is a key somewhere else in the dungeon." << endl;
}


/***************************************************************************************
**Takes an item that the player uses and tries to unlock the exit door. If the item
**is the exit key, player wins and escapes dungeon, otherwise the player takes damage.
****************************************************************************************/
void EndSpace::interact(Item n)
{

	cout << "There are skeletons surrounding the door, and faded handprints of old, \ndried blood all over it. This is the exit." << endl;
	cout << endl;

	if (n.isKey() == true)
	{
		cout << "You approach the door slowly, moving fragile bones out of the way. \nYou get the key out of your pocket. \n"
			<< "As you unlock the door, you can feel the poison air disperse. \nThe door opens, and you step out into the light." << endl;

		openDoor = true;
	}
	else
	{
		cout << "The door is locked! " << n.getItemName() << " had no effect! You can feel the poison air filling you lungs. You must hurry." << endl;
		user->subHP(5);
		cout << "You take five points of damage." << endl;
	}

}
