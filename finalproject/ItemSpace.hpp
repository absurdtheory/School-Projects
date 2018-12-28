/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: ItemSpace Class Header, derived from Space Class
*****************************************************************************/
#ifndef ITEMSPACE_HPP
#define ITEMSPACE_HPP
#include "Space.hpp"

class ItemSpace : public Space
{
private:
	int genRoomItem;				//holds number for room item generated
	int genInvenItem;				//holds number for inventory item generate
	bool findItem;					//true if player will find an item, otherwise false
	bool foundItem = false;			//indicates if player has found an item or not



public:
	ItemSpace(Player *p);
	virtual void investigate();
	virtual void interact(Item);
	~ItemSpace();

};

#endif