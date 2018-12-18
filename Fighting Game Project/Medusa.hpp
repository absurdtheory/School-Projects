/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Header for Medusa class, derived from BaseChar.
*********************************************************************************/
#ifndef MEDUSA_HPP
#define MEDUSA_HPP
#include "BaseChar.hpp"

class Medusa : public BaseChar
{
public:
	Medusa();										//default constructor to initialize variables
	virtual int rollAttack();						//overrides BaseChar rollAttack
	virtual int rollDefense();						//overrides	BaseChar rollDefense
	virtual bool specialAttack(BaseChar *ptr1);		//overrides BaseChar specialAttack, takes a BaseChar pointer

};


#endif