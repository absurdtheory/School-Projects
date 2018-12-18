/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Functions for HarryPotter class.
*********************************************************************************/
#include "HarryPotter.hpp"

/***********************************************************
**Default constructor to initialized name, armor, strength,
**charact, and sAttack
************************************************************/
HarryPotter::HarryPotter()
{
	name = "Harry Potter";
	armor = 0;
	strength = 10;
	baseStrength = 10;
	charact = "Harry Potter is a wizard.";
	sAttack = HOGWARTS;
}


/***********************************************************
**Rolls 2d6 and displays the results of each roll. Returns
**the total attack value
************************************************************/
int HarryPotter::rollAttack() 
{
	int d1 = (rand() % 6 + 1);
	int d2 = (rand() % 6 + 1);

	//cout << this->getName() << " rolled attack  with results " << d1 << " and " << d2 << endl;

	attack = d1 + d2;

	return attack;
}


/***********************************************************
**Rolls 2d6 and displays the results of each roll. Returns
**the total defense value
***********************************************************/
int HarryPotter::rollDefense() 
{
	int d1 = (rand() % 6 + 1);
	int d2 = (rand() % 6 + 1);

	//cout << this->getName() << " rolled defense 2d6 with results " << d1 << " and " << d2 << endl;

	defense = d1 + d2;

	return defense;
}


/*********************************************************
**If strength is less than or equal to zero, Harry Potter
**is revived with strength 20, sAttack is changed from
**HOGWARTS to NONE, and returns true. (Can only be revived once)
**********************************************************/
bool HarryPotter::specialAttack(BaseChar *ptr1)
{
	if (this->getStrength() <= 0 && this->getSpecial() == HOGWARTS)
	{
		baseStrength = 20;
		this->setStrength(20);
		this->setSpecial(NONE);
		//cout << "Harry Potter used Hogwarts and recovered!" << endl;

		return true;
	}
	return false;
}