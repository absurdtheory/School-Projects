/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: KeySpace header
*****************************************************************************/
#ifndef KEYSPACE_HPP
#define KEYSPACE_HPP
#include "Space.hpp"

class KeySpace : public Space
{
private:

	bool keyTaken;						//holds if player had taken the key or not

public:

	KeySpace(Player *p);
	virtual void investigate();
	virtual void interact(Item p);
	void smashBox();					//breaks open the box the key is in if player to allow player to get key if they do not have the gem
	~KeySpace();
};

#endif