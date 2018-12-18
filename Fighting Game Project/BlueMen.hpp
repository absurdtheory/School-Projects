/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Header for class BlueMen, derived from BaseChar
*********************************************************************************/
#ifndef BLUEMEN_HPP
#define BLUEMEN_HPP
#include "BaseChar.hpp"

class BlueMen : public BaseChar
{
private:
	int defDice;									//holds current number of defense die
	BaseChar *temp;

public:
	BlueMen();										//default constructor to initialized variables
	virtual int rollAttack();						//overrides BaseChar rollAttack
	virtual int rollDefense();						//overrides BaseChar rollDefense
	virtual bool specialAttack(BaseChar *ptr1);		//overrides BaseChar specialAttack, takes a BaseChar pointer
	virtual void recovery();						//overrides BaseChar recovery
};




#endif