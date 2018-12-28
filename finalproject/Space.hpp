/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/2018
**Description: Header for Space Class, which is the parent class of BlankSpace,
**KeySpace, TrapSpace, ItemSpace, and EndSpace. It is an abstract class.
*****************************************************************************/
#ifndef SPACE_HPP
#define SPACE_HPP
#include <string>
#include <iostream>
#include <cstdlib>
#include "Item.hpp"
#include "Player.hpp"
using std::string;
using std::cout;
using std::endl;
using std::cin;

class Space
{
protected:
	string spaceDesc;					//holds a basic description of a space
	Player *user;						//pointer to the player
	bool openDoor = false;				//true if the exit door is open
	bool trapSpace = false;				//true if player is in a trap room and trap is armed

public:
	Space *top = NULL;
	Space *right = NULL;
	Space *left = NULL;
	Space *bottom = NULL;

	string getSpaceDesc();				
	bool getOpenDoor();
	bool getTrapSpace();
	void setTrapSpace(bool);
	virtual void investigate() = 0;		//pure virtual function 
	virtual void interact(Item) = 0;	//pure virtual function
	virtual ~Space();
};

#endif