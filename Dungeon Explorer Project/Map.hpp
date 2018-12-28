/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: Header for Map class. Creates the dungeon layout, moves the 
**player around the dungeon.
*****************************************************************************/
#ifndef MAP_HPP
#define MAP_HPP
#include "Space.hpp"
#include "BlankSpace.hpp"
#include "TrapSpace.hpp"
#include "EndSpace.hpp"
#include "ItemSpace.hpp"
#include "KeySpace.hpp"


class Map
{
private:
	Space *playerLocation;						//pointer to player's location in the dungeon
	Space *placeholder;							//used to allocate memory
	Space *temp;								//used to deallocate memory
	Space *start;								//holds start of dungeon
	Space *end;									//holds end of dungeon
	Player *user;								//pointer to the player


public:
	Map(Player *p);								//create layout
	bool movePlayer(int);						//move player to new space
	Space *getPlayer();							//returns the pointer to player's location
	~Map();										//deallocate memory


};

#endif