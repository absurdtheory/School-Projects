/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Functions for Barbarian class.
*********************************************************************************/
#include "Barbarian.hpp"

/***********************************************************
**Default constructor to initialized name, armor, strength,
**charact, and sAttack
************************************************************/
Barbarian::Barbarian()
{
	name = "Barbarian";
	armor = 0;
	strength = 12;
	baseStrength = 12;
	charact = "Think Conan or Hercules from the movies. Big Sword, big muscles, bare torso.";
	sAttack = NONE;
}


/************************************************************
**Rolls 2d6, displays the results of each roll and returns 
**the total attack value
************************************************************/
int Barbarian::rollAttack() 
{
	int d1 = (rand() % 6 + 1);
	int d2 = (rand() % 6 + 1);

	//cout << this->getName() << " rolled attack 2d6 with results " << d1 << " and " << d2 << endl;

	attack = d1 + d2;
	return attack;
}


/************************************************************
**Rolls 2d6, displays the results of each roll and returns
**the total defense value
************************************************************/
int Barbarian::rollDefense() 
{
	int d1 = (rand() % 6 + 1);
	int d2 = (rand() % 6 + 1);

	//cout << this->getName() << " rolled defense 2d6 with results " << d1 << " and " << d2 << endl;

	defense = d1 + d2;

	return defense;
}

/********************************************************
**Does not have a special attack, always returns false
********************************************************/
bool Barbarian::specialAttack(BaseChar *ptr1)
{
	return false;
}