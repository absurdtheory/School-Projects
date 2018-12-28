/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: Header for TrapSpace class. Derived from Space class.
*****************************************************************************/
#ifndef TRAPSPACE_HPP
#define TRAPSPACE_HPP
#include "Space.hpp"

class TrapSpace : public Space
{
private:
	int perception,				//holds perception roll
		disarm;					//holds disarm roll
	bool trapDeactivated;		//if trap is disarmed/ deactivate/ already activated, don't trigger next time the user enter the space
	bool trapNoticed = false;

public:
	TrapSpace(Player *p);		//constructor that takes a pointer to player
	void rollPerception();		
	void rollDisarm();
	void springTrap();
	int trapDamage();			//returns the damage the trap causes
	virtual void investigate();
	virtual void interact(Item);

};

#endif