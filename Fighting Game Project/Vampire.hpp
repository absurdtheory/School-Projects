/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Header for class Vampire, derived from BaseChar.
*********************************************************************************/
#ifndef VAMPIRE_HPP
#define VAMPIRE_HPP
#include "BaseChar.hpp"

class Vampire : public BaseChar
{
public:
	Vampire();										//default constructor to initialized variables
	virtual int rollAttack();						//overrides BaseChar rollAttack
	virtual int rollDefense();						//overrides BaseChar rollDefense
	virtual bool specialAttack(BaseChar *ptr1);		//overrides BaseChar specialAttack, takes a BaseChar pointer

};


#endif