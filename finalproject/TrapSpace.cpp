/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: TrapSpace class functions. There is a  60% chance of the player
**noticing the trap and being given the option to disarm it by hand, which has
**1/3 chance of succeeding. Alternatively, the player can use wire cutters to 
**disarm the trap with 100% success rate if they have them in their inventory.
*****************************************************************************/
#include "TrapSpace.hpp"
#include "Inputvalid.hpp"

/***************************************************************************************
**Constructor that initializes variables, takes a pointer to the player
****************************************************************************************/

TrapSpace::TrapSpace(Player *p)
{
	spaceDesc = "There is something odd about this room... You decide to investigate.";
	trapDeactivated = false;
	user = p;
	rollPerception();
	trapSpace = true;
}


/***************************************************************************************
**Rolls perception check to see if player notices the trap
****************************************************************************************/
void TrapSpace::rollPerception()
{
	perception = (rand() % 10 + 1);
}


/***************************************************************************************
**Rolls a disarm check to see if play can disarm trap with hands
****************************************************************************************/
void TrapSpace::rollDisarm()
{
	disarm = (rand() % 3 + 1);
}


/***************************************************************************************
**Rolls trap damage taken by player if trap is activated
****************************************************************************************/
int TrapSpace::trapDamage()
{
	return (rand() % 6 + 1);
}


/***************************************************************************************
**Displays where any adjacent rooms are. Forces an interaction with the trap if the player
**notices it. Gives them the option to disarm it with their hands. Displays a discription 
**of the room that changes base on if the trap is still armed.
****************************************************************************************/
void TrapSpace::investigate()
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
	
	if (trapSpace == false)
	{
		trapDeactivated = true;
	}
	cout << endl;

	if (perception < 7 && trapDeactivated == false)
	{
		int choice;
		
		cout << "You notice a trip wire trap on the floor! Maybe you can use and item to disarm it?" << endl;
		
		cout << "Alternatively you could try to disarm it by hand.\nWould you like to try to disarm it by hand?\n"
			<< "1. Yes		2. No" << endl;

		cin >> choice;

		while (!inputValid(choice) || choice < 1 || choice > 2)
		{
			cout << "Error: Please re-enter your selection." << endl;
			cin >> choice;
		}

		trapNoticed = true;

		if (choice == 1)
		{
			rollDisarm();
			if (disarm == 1)
			{
				cout << "You successfully disarmed the trap!" << endl;
				trapDeactivated = true;
				trapSpace = false;
				spaceDesc = "This room had the trap in it. It is now disarmed.";
			}
			else
			{
				cout << "You fumble with the wires and the trap activates!" << endl;
				int damage = trapDamage();
				user->subHP(damage);
				cout << "You took " << damage << " points of damage and your health is now " << user->getHP() << endl;
				trapDeactivated = true;
				trapSpace = false;
				spaceDesc = "This room had the trap in it. It is now disarmed.";
			}
		}
		
	}
	else if (trapDeactivated == true)
	{
		cout << "The trap is no longer active." << endl;
	}
	else if(trapNoticed == false)
	{
		cout << "Upon closer inspection, you don't notice anything obviously out of the ordinary.\n" 
			<< "As you move around the room, you accidently trigger a trap!\n" << endl;

		int damage = trapDamage();
		user->subHP(damage);

		cout << "You took " << damage << " points of damage and your health is now " << user->getHP() << endl;
		trapDeactivated = true;
		trapSpace = false;
		spaceDesc = "This room had the trap in it. It is now disarmed.";
	}
	else
	{
		cout << "The trap is still there. Maybe it can be disarmed." << endl;
	}

}


/***************************************************************************************
**Allows player to interact with the trap/room by using an item. If the item used is wire
**cutters and the trap is still active, the trap is disarmed, otherwise no effect.
****************************************************************************************/
void TrapSpace::interact(Item n)
{
	if (n.getItemName() == "wire cutters" && trapDeactivated == false)
	{
		cout << "You successfully disarmed the trap with the wire cutters! \nUnfortunately they broke in the process." << endl;
		trapDeactivated = true;
		trapSpace = false;
		user->dropItem(n);
		spaceDesc = "This room had the trap in it. It is now disarmed.";
	}
	else if (trapDeactivated == false)
	{
		cout << n.getItemName() << " had no effect.";
	}
	else
	{
		cout << "Nothing happened." << endl;
	}
}