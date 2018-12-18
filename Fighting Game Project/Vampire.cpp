/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Functions for Vampire class
*********************************************************************************/
#include "Vampire.hpp"

/***********************************************************
**Default constructor to initialized name, armor, strength,
**charact, and sAttack
************************************************************/
Vampire::Vampire()
{
	name = "Vampire";
	armor = 1;
	strength = 18;
	baseStrength = 18;
	charact = "Sauve, debonair, but vicious and suprisingly resilient.";
	sAttack = CHARM;
}


/************************************************************
**Rolls 1d12, displays the results and returns the attack value
*************************************************************/
int Vampire::rollAttack() 
{
	attack = (rand() % 12 + 1);

	//cout << this->getName() << " rolled attack 1d12 with result " << attack << endl;

	return attack;
}


/*************************************************************
**Rolls 1d6, displays the results, and returns the defense value
**************************************************************/
int Vampire::rollDefense() 
{
	defense = (rand() % 6 + 1);

	//cout << this->getName() << " rolled defense 1d6 with result " << defense << endl;

	return defense;
}

/************************************************************
**Has a 50% chance of charming the opponent into not attack
**for a turn. If charm succeeds, displays message stating 
**opponent cannot attack using BaseChar pointer parameter. It
**also returns true. Otherwise, returns false.
*************************************************************/
bool Vampire::specialAttack(BaseChar *ptr1)
{
	int special = (rand() % 2 + 1);

	if (special == 1)
	{
		//cout << ptr1->getName() << " was Charmed and can not attack!" << endl;
		return true;
	}

	return false;
}