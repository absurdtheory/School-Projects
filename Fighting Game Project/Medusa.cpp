/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Functions for Medusa class.
*********************************************************************************/
#include "Medusa.hpp"

/***********************************************************
**Default constructor to initialized name, armor, strength,
**charact, and sAttack
************************************************************/
Medusa::Medusa()
{
	name = "Medusa";
	armor = 3;
	strength = 8;
	baseStrength = 8;
	charact = "Scrawny lady with snakes for hair which helps her during combat. Just don't look at her!";
	sAttack = GLARE;
}


/************************************************************
**Rolls 2d6, displays the results of each roll and returns
**the total attack value
************************************************************/
int Medusa::rollAttack() 
{
	int d1 = (rand() % 6 + 1);
	int d2 = (rand() % 6 + 1);

	//cout << this->getName() << " rolled attack 2d6 with results " << d1 << " and " << d2 << endl;

	attack = d1 + d2;

	return attack;
}


/************************************************************
**Rolls 1d6, displays the result, and returns the attack value
************************************************************/
int Medusa::rollDefense() 
{
	
	defense = (rand() % 6 + 1);

	//cout << this->getName() << " rolled defense 1d6 with result " << defense << endl;

	return defense;
}

/***********************************************************
**If Medusa rolls a total of 12, the opponent is petrified
**and dies. Returns true. If the opponent has the special 
**attack, Hogwarts, they come back to life. Otherwise, 
**returns false.
************************************************************/
bool Medusa::specialAttack(BaseChar *ptr1)
{
	if (attack == 12)
	{
		//cout << this->getName() << " used Glare!" << endl;
		//cout << ptr1->getName() << " was turned to stone and died." << endl;

		ptr1->setStrength(0);

		if (ptr1->getSpecial() == HOGWARTS)
		{
			ptr1->specialAttack(this);
		}

		return true;
	}

	return false;

}