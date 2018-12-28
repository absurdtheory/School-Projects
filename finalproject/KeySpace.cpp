/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: KeySpace functions, derived from Space class.
*****************************************************************************/
#include "KeySpace.hpp"
#include "Inputvalid.hpp"

/***************************************************************************************
**Constructor that initializes variables, takes a pointer to the player
****************************************************************************************/
KeySpace::KeySpace(Player *p)
{
	user = p;
	keyTaken = false;
	spaceDesc = "The room is brightly lit, but you see no lights.\n There is a table in the middle with a small box on it.";
	
}


/***************************************************************************************
**Investigates the room. Displays where adjacent rooms are, gives the player information
**about the room, and asks if player wants to smash open the box the key is in.
****************************************************************************************/
void KeySpace::investigate() 
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
	
	if (keyTaken == false)
	{
		int choice;

		cout << "You take a closer look at the box, it is decorated ornately \nand seems to be missing an gem.\n"
			<< "It seems flimsy enough that you could open it by smashing it on the ground." << endl;

		cout << "Would you like to smash it on the ground?\n"
			<< "1. Yes		2. No" << endl;

		cin >> choice;

		while (!inputValid(choice) || choice < 1 || choice >2)
		{
			cout << "Error: please re-enter your selection." << endl;
			cin >> choice;
		}

		if (choice == 1)
		{
			smashBox();
		}

		else
		{
			cout << "Probably a wise decision...";
			cout << endl;
		}

	}
	else
	{
		cout << "This is the room where you found the key." << endl;
	}
}


/***************************************************************************************
**takes an item used by the player. If the player uses a peculiar gem, the box opens and
**the player gets the key without the player taking damage. Otherwise, there is not effect.
****************************************************************************************/
void KeySpace::interact(Item n)
{
	if (n.getItemName() == "a peculiar gem")
	{
		cout << "You insert the gem and hear the whirring of gears.\nThe box pops open and you find a simple key inside." << endl;
		
		cout << "Perhaps this key will unlock the way out of the dungeon?" << endl;
		user->addItem(user->createItem("a simple key", "Perhaps this key will unlock the way out of the dungeon?"));
		user->dropItem(n);

	}
	else
	{
		cout << n.getItemName() << " has no effect." << endl;
	}

}


/***************************************************************************************
**If the player decides to smash open the box, the player receives the key but takes
**damage.
****************************************************************************************/
void KeySpace::smashBox()
{
	cout << "You throw the box to the ground and it bursts open,\nreleasing a cloud of noxious gas.\n\n"
		<< "Through the cloud you find a key on the floor,\nbut you take 5 points of damage." << endl;

	cout << "Perhaps this key will unlock the way out of the dungeon?" << endl;

	user->addItem(user->createItem("a simple key", "Perhaps this key will unlock the way out of the dungeon?"));
	user->subHP(5);
	cout << endl;
}

KeySpace::~KeySpace()
{
	//cout << "keyspace destructor" << endl;
}