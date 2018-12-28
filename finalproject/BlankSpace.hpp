/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: Header for BlankSpace, derived class of Space
*****************************************************************************/
#ifndef BLANKSPACE_HPP
#define BLANKSPACE_HPP
#include "Space.hpp"

class BlankSpace : public Space
{
private:

public:
	BlankSpace(Player *p);
	virtual void investigate();
	virtual void interact(Item);

};

#endif