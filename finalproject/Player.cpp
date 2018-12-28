/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: Functions for Player Class.
*****************************************************************************/
#include "Player.hpp"
#include "Inputvalid.hpp"

/***************************************************************************************
**Default Constructor that initializes variables.
****************************************************************************************/
Player::Player()
{
	HP = 20;
	maxHP = 20;
}


/***************************************************************************************
**Returns HP
****************************************************************************************/
int Player::getHP()
{
	return HP;
}


/***************************************************************************************
**Subtracts a int parameter from HP
****************************************************************************************/
void Player::subHP(int n)
{
	HP -= n; 
}


/***************************************************************************************
**Adds an int n parameter HP. If it adds more than Maxhealth, only adds part of n.
****************************************************************************************/
void Player::addHP(int n)
{
	if ((HP + n) > maxHP)
	{
		int temp = (HP + n) - maxHP;
		HP += temp;
	}
	else
	{
		HP += n;
	}
}


/***************************************************************************************
**Decrements HP by one. Used as player moves between spaces.
****************************************************************************************/
void Player::decHP()
{
	HP--;
}


/***************************************************************************************
**Displays the inventory vector of items
****************************************************************************************/
void Player::showInventory()
{
	//display current inventory
	if (inventory.size() == 0)
	{
		cout << "Your inventory is empty" << endl;
	}
	else
	{
		cout << "Inventory (max of two items):" << endl;
		for (int i = 0; i < inventory.size(); i++)
		{
			cout << i + 1 << ". " << inventory[i].getItemName() << endl;
		}
	}
}


/***************************************************************************************
**Returns the inventory vector size
****************************************************************************************/
int Player::getInvSize()
{
	return inventory.size();
}


/***************************************************************************************
**Returns an item in the vector
****************************************************************************************/
Item Player::getItem(int i)
{
	return inventory[i];
}


/***************************************************************************************
**Creates an and returns an Item that is initialized with two strings
****************************************************************************************/
Item Player::createItem(string n, string d)
{
	Item temp;
	temp.setItemName(n);
	temp.setDesc(d);

	if (n == "a simple key")
	{
		temp.setExitKey(true);
	}

	return temp;
}


/***************************************************************************************
**Receives an item as a parameter that is then removed from inventory
****************************************************************************************/
void Player::dropItem(Item n)
{
	int i = 0;
	

	while (n.getItemName() != inventory[i].getItemName()) //will this work?
	{
		i++;
	}

	inventory.erase(inventory.begin() + i);  //will this work?
}


/***************************************************************************************
**Adds an item to the inventory. Forces the player to drop an item if inventory is full.
**Does not allow the player to drop the key to the exit.
****************************************************************************************/
void Player::addItem(Item n)
{
	if (inventory.size() != 2)
	{
		inventory.push_back(n);
	}
	else
	{
		int select;
		
		cout << "Inventory full. Choose an item to discard:" << endl;
		showInventory();

		cin >> select;
		while (!inputValid(select) || select < 1 || select > 2)
		{
			cout << "Error: please re-enter selection:" << endl;
			cin >> select;
		}

		while (inventory[select - 1].getItemName() == "a simple key")
		{
			cout << "That seems important, you can't drop that.\n"
				<< "Choose a different item to drop:";

			cin >> select;
			while (!inputValid(select) || select < 1 || select > 2)
			{
				cout << "Error: please re-enter selection:" << endl;
				cin >> select;
			}
		}

		dropItem(inventory[select - 1]);

		inventory.push_back(n);
	}

}

Player::~Player()
{
	//cout << "player destructor" << endl;
}

