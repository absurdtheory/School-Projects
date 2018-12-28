/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date:
**Description:
*****************************************************************************/
#include "ItemSpace.hpp"

/***************************************************************************************
**Constructor that initializes variables, generates a number to decide what object should
**be generate in the room for the player to interact with. Decides if player will find an
**item, and generate what item the player may find. Takes a point to the player.
****************************************************************************************/
ItemSpace::ItemSpace(Player *p)
{
	//generate a number 1-4 for an item to interact with in the room
	genRoomItem = (rand() % 4 + 1);

	user = p;
	
	if (genRoomItem == 1)
	{
		spaceDesc = "You enter a room with a mirror in the middle.\nThere's nothing else of note in the room.";
	}

	else if (genRoomItem == 2)
	{
		spaceDesc ="There is a fountain in the corner of the room.\nThere are many skeletons surrounding it.";
	}

	else if (genRoomItem == 3)
	{
		spaceDesc = "The room is a bit brighter than the others,\nyou notice a torch on one of the walls.";
	}

	else
	{
		spaceDesc = "At first the room appears empty, however a closer inspection\nreveals a grate in the center of the floor.";
	}

	
	//75% percent chance of that item having an inventory item
	int findItemChance = (rand() % 4 + 1);

	if (findItemChance != 1)
	{
		findItem = true;
	}
	else
	{
		findItem = false;
	}
	
	//generate a number 1-3 for an inventory item
	genInvenItem = (rand() % 3 + 1);
}


/***************************************************************************************
**Investigates the room, shows where adjacent rooms are. If the player finds an item,
**adds it to inventory. Displays a description based on room item and inventory item
**generated.
****************************************************************************************/
void ItemSpace::investigate()
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

	if (findItem == true && foundItem == false)
	{
		if (genRoomItem == 1)
		{
			cout << "A strangely clean mirror. You can see your reflection, \nbut there is something odd about it." << endl;
			cout << "You notice one of the corners is cracked.\nUpon closer inpection you find ";
		}
		else if (genRoomItem == 2)
		{
			cout << "A long-since dried - up fountain.\nYou think you see something glinting in the basin." << endl;
			cout <<"Hidden in the drain, you find a ";
		}
		else if (genRoomItem == 3)
		{
			cout << "There is an lit torch affixed to the wall.\nYou wonder how long it's been burning for." << endl;
			cout << "There is a hole in the wall next to the torch.\nUpon examination, you find ";
		}
		else
		{
			cout << "The grate is rusty, and appears to cover a shallow pit.\nYou could probably squeeze your arm through." << endl;
			cout << "You stick your arm in the grate and feel around. You find ";
		}

		if (genInvenItem == 1)
		{
			cout << "wire cutters" << endl;
			cout << "They seem very frail and will most likely break after use." << endl;
			user->addItem(user->createItem("wire cutters", "They seem very frail and will most likely break after use."));
		}

		if (genInvenItem == 2)
		{
			cout << "an eyeball" << endl;
			cout << "It's oddly preserved. Somehow you know this will restore 5 health if consumed." << endl;
			user->addItem(user->createItem("an eyeball", "It's oddly preserved. Somehow you know this will restore 5 health if consumed."));
		}

		if (genInvenItem == 3)
		{
			cout << "a peculiar gem" << endl;
			cout << "Maybe it goes to something?" << endl;
			user->addItem(user->createItem("a peculiar gem", "Maybe it goes to something?"));
		}
		foundItem = true;
	}
	else
	{
		if (genRoomItem == 1)
		{
			cout << "A strangely clean mirror.You can see your reflection, \nbut there is something odd about it." << endl;
			cout << "You stare at the mirror for a while.\nDid you always look like that?" << endl;
		}
		else if (genRoomItem == 2)
		{
			cout << "A long-since dried - up fountain.\nYou think you see something glinting in the basin." << endl;
			cout << "Your eyes were deceiving you, you don't find anything." << endl;
		}
		else if (genRoomItem == 3)
		{
			cout << "There is an lit torch affixed to the wall.\nYou wonder how long it's been burning for." << endl;
			cout << "You try to take the torch, but it's stuck." << endl;
		}
		else
		{
			cout << "The grate is rusty, and appears to cover a shallow pit.\nYou could probably squeeze your arm through." << endl;
			cout << "You stick your arm in the grate and feel around.\nYou feel something slimy brush across your hand and quickly retract it." << endl;
		}
	}

}

/***************************************************************************************
**If the player uses an item on this room, there is not effect
****************************************************************************************/
void ItemSpace::interact(Item n)
{
	cout << n.getItemName() << " had no effect." << endl;
}

ItemSpace::~ItemSpace()
{
	//cout << "delete itemspace"<< endl;
}