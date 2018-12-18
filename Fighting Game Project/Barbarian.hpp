/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Header for Barbarian class, derived from BaseChar
*********************************************************************************/
#ifndef BARBARIAN_HPP
#define BARBARIAN_HPP
#include "BaseChar.hpp"

class Barbarian : public BaseChar
{
public:
	Barbarian();									//default constructor to initialize variables
	virtual int rollAttack();						//overrides BaseChar rollAttack
	virtual int rollDefense();						//overrides BaseChar rollDefense
	virtual bool specialAttack(BaseChar *ptr1);		//overrides BaseChar specialAttack, takes a BaseChar pointer, always returns false

};


#endif