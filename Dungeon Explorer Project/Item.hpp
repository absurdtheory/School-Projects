/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date:	3/16/18
**Description: Header for Item Class
*****************************************************************************/
#ifndef ITEM_HPP
#define ITEM_HPP
#include <string>
using std::string;

class Item
{
private:
	string itemName,
		itemDesc;
	bool exitKey = false;				//true if item is the key to the exit

public:
	void setItemName(string n);
	string getItemName();
	void setDesc(string n);
	string getDesc();
	bool isKey();						//returns true if item is the exit key, otherwise returns false
	void setExitKey(bool);				//sets an item to be an exit key, takes bool parameter

};

#endif