/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: Header for EndSpace
*****************************************************************************/
#ifndef ENDSPACE_HPP
#define ENDSPACE_HPP
#include "Space.hpp"


class EndSpace : public Space
{
private:

public:
	EndSpace(Player *p);
	virtual void investigate();
	virtual void interact(Item n);


};

#endif