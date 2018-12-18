/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: header for HarryPotter class, derived from BaseChar.
*********************************************************************************/
#ifndef HARRYPOTTER_HPP
#define HARRYPOTTER_HPP
#include "BaseChar.hpp"

class HarryPotter : public BaseChar
{
public:
	HarryPotter();									//default constructor for initializing variables
	virtual int rollAttack();						//overrides BaseChar rollAttack
	virtual int rollDefense();						//overrides BaseChar rollDefense
	virtual bool specialAttack(BaseChar *ptr1);		//overrides BaseChar special Attack, takes a BaseChar pointer

};

#endif