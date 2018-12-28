/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: Header for Player class
*****************************************************************************/
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include <vector>
#include <iostream>
#include "Item.hpp"
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;

class Player
{
private:

	int HP,										//holds player's health
		maxHP;									//holds max health a player can have
	vector <Item> inventory;					//vector of items. Can hold a max of two.


public:
	Player();					
	int getHP();
	void subHP(int);
	void addHP(int);
	void decHP();
	void showInventory();					//displays the vector
	int getInvSize();						//returns size of vector
	Item getItem(int);						//returns an item in the vector
	Item createItem(string n, string d);	//creates an item
	void dropItem(Item);					//removes an item from the vector
	void addItem(Item n);					//adds an item to the vector
	~Player();

};

#endif