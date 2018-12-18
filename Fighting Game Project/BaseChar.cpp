/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Functions for base class, BaseChar.
*********************************************************************************/
#include "BaseChar.hpp"

/*********************************************
**Returns armor
**********************************************/
int	BaseChar::getArmor()
{
	return armor;
}


/***********************************************
**takes an int and sets strength to it
************************************************/
void BaseChar::setStrength(int s)
{
	strength = s;
}


/***********************************************
**returns strength
***********************************************/
int	BaseChar::getStrength()
{
	return strength;
}

/**************************************************
**returns damage
**************************************************/
int BaseChar::getDamage()
{
	return damage;
}


/*************************************************
**takes an int and set damage to it
**************************************************/
void BaseChar::setDamage(int d)
{
	damage = d;
}


/*************************************************
**returns charact- not currently implemented
**************************************************/
string BaseChar::getCharact()
{
	return charact;
}


/*************************************************
**returns name
**************************************************/
string BaseChar::getName()
{
	return name;
}


/**************************************************
**takes enum Special datatype and sets sAttack to it
**************************************************/
void BaseChar::setSpecial(Special a)
{
	sAttack = a;
}


/*****************************************************
**Returns sAttack
******************************************************/
Special BaseChar::getSpecial()
{
	return sAttack;
}


/*****************************************************
**Sets user-defined character name
******************************************************/
void BaseChar::setcharName(string n)
{
	charName = n;
}


/****************************************************
**Gets user-defined character name
*****************************************************/
string BaseChar::getcharName()
{
	return charName;
}


/*******************************************************
**Recovers a random amount of strength based off of 
**a how much strength was lost
*******************************************************/
void BaseChar::recovery()
{
	
	if (strength != baseStrength && damage != 0)
	{
		int recover = (rand() % damage + 1);

		this->setStrength(strength + recover);

		cout << this->getName() << " rolled a recover of " << recover << " and their new strength is " << strength << endl;
	
	}
}