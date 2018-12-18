/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Header for the base class, BaseChar. 
*********************************************************************************/
#ifndef BASECHAR_HPP
#define	BASECHAR_HPP
#include <string>
#include <cstdlib>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;

enum Special{NONE, CHARM, MOB, GLARE, HOGWARTS};	//enum for special abilities

class BaseChar
{
protected:
	int attack,
		defense,
		armor,
		strength,
		damage,
		baseStrength;								//holds the character's starting strength, does not change
	string charact,									//holds character's description, not currently accessed in program
		name,										//holds the character's name
		charName;									//holds character's user-defined name
	Special sAttack;								//holds the character's special ability


public:
	virtual int rollAttack() = 0;					//pure virtual function to roll attack die
	virtual int rollDefense() = 0;					//pure virtual function to roll defense die
	int	getArmor();									//returns armor
	void setStrength(int);							//takes an int and sets strength
	int	getStrength();								//returns strength
	int getDamage();								//returns damage
	void setDamage(int d);							//takes an int and sets damage
	string getCharact();							//returns charact - not implemented currently
	string getName();								//returns name
	void setSpecial(Special);						//sets sAttack, takes enum special
	Special getSpecial();							//returns sAttack
	virtual bool specialAttack(BaseChar *ptr1)= 0;	//checks if special ability is activated, takes a BaseChar pointer, returns true if activated

	//new functions
	void setcharName(string n);						//sets user-defined name
	string getcharName();							//gets user-defined name
	virtual void recovery();						//regenerates winner's strength
};

#endif