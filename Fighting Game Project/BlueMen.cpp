/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Functions for BlueMen class. 
*********************************************************************************/
#include "BlueMen.hpp"

/***********************************************************
**Default constructor to initialized name, armor, strength,
**charact, defDice, and sAttack
***********************************************************/
BlueMen::BlueMen()
{
	name = "Blue Men";
	armor = 3;
	strength = 12;
	baseStrength = 12;
	charact = "They are small, 6 inches tall, but fast and tough. They are hard to hit so they cantake some damage.\n They can also do a LOT of damage when they crawl inside enemies' armor or clothing.";
	defDice = 3;
	sAttack = MOB;
}

/************************************************************
**Rolls 2d6 and displays the results of each roll. Returns
**the total attack value
************************************************************/
int BlueMen::rollAttack() 
{
	int d1 = (rand() % 10 + 1);
	int d2 = (rand() % 10 + 1);

	//cout << this->getName() << " rolled attack 2d10 with results " << d1 << " and " << d2 << endl;

	
	attack = d1 + d2;

	return attack;
}

/***************************************************************
**Rolls 1-3d6 depending on the number of defense dice. Displays
**the results of each roll and returns the total defense value.
*****************************************************************/
int BlueMen::rollDefense() 
{
	//cout << this->getName() << " rolled defense " << defDice << "d6 with results ";
	
	int dice;
	defense = 0;

	for (int i = 0; i < defDice; i++)
	{
		dice = (rand() % 6 + 1);
		defense += dice;
		//cout << dice << " ";
	}
	//cout << endl;

	return defense;
}


/***********************************************************
**Adjusts defDice based on current strength. Returns true if
**dice are adjusted, otherwise returns false. Takes a
**BaseChar pointer which is not used for anything.
***********************************************************/
bool BlueMen::specialAttack(BaseChar *ptr1)
{
	
	if (this->getStrength() <= 0)
	{
		return false;
	}
	
	if (this->getStrength() <= 4)
	{
		defDice = 1;
		//cout << "Blue Men now has one defense die!" << endl;
		return true;
	}
	else if (this->getStrength() <= 8)
	{
		defDice = 2;
		//cout << "Blue Men now has two defense dice!" << endl;
		return true;
	}
	else
	{
		defDice = 3;
		//cout << "Blue Men now has three defense dice!" << endl;
	}

	return false;
}

/***********************************************************
**Adjusts defDice based on current strength. Returns true if
**dice are adjusted, otherwise returns false. Takes a
**BaseChar pointer which is not used for anything.
***********************************************************/
void BlueMen::recovery()
{
	if (strength != baseStrength && damage != 0)
	{
		int recover = (rand() % damage + 1);

		this->setStrength(strength + recover);

		//cout << this->getName() << " rolled a recover of " << recover << " and their new strength is " << strength << endl;

		this->specialAttack(temp);
	}
}