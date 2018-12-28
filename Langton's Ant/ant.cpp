/************************************************************************
**Program: Project 1
**Author: Alexis Tucker
**Date: 1/17/2018
**Description: Defines ant class constructor, functions, and deconstructor.
**Descriptions of individual functions below.
*************************************************************************/
#include <iostream>
#include <iomanip>
#include "Ant.hpp"
using std::cout;
using std::endl;


/****************************************************************************
**Constructor that four int parameters, the number of rows and columns, 
** and the ant's starting row and column, and one enum parameter that 
**sets the direction the ant is facing. A 2D array is created based on 
** the number of rows and columns and it is initialized with whitespace.
****************************************************************************/
Ant::Ant(int r, int c, int ar, int ac, Orient ao)
{
	//create array
	row = r;
	col = c;
	ant_row = ar - 1;
	ant_col = ac - 1;
	ant_Array = new char*[row];                 
	for (int i = 0; i < row; i++)
	{
		ant_Array[i] = new char[col];
	}


	//fill array with whitespace
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			ant_Array[r][c] = ' ';
		}
	}

	//current ant location color
	board_Color = ' ';

	//place ant on board
	ant_Array[ant_row][ant_col] = '*';


	//set initial orientation of the ant
	setOrientation(ao);
}


/********************************************************************
**sets the direction the ant is facing
*********************************************************************/
void Ant::setOrientation(Orient ao)
{
	orientation = ao;
}

/********************************************************************
**returns the direction the ant is facing
*********************************************************************/
Orient Ant::getOrientation()
{
	return orientation;
}

/************************************************************************
**Prints the current board on the screen
*************************************************************************/
void Ant::printBoard()
{
	//upper boarder
	for (int c = 0; c < col; c++)
	{
		cout << "-----";
	}
	cout << endl;


	for (int i = 0; i < row; i++)
	{
		cout << '|';													//left boarder
		for (int s = 0; s < col; s++)
		{
			
			cout << std::setw(3)<< ant_Array[i][s] << std::setw(3);
			
		}
		cout << '|' << endl;											//right boarder
	}

	//lower boarder
	for (int c = 0; c < col; c++)
	{
		cout << "-----";
	}
	cout << endl;
}

/*****************************************************************************
**Moves the ant on the board based on the color of the space the ant is
**on and the direction it is facing. If the ant tried to move out of bounds,
**the board wraps around the the ant appears on the other side
*****************************************************************************/
void Ant::moveAnt()
{
	if (board_Color == ' ')
	{
		if (getOrientation() == UP)
		{
			//change direction ant is facing
			setOrientation(RIGHT);

			//update board color
			ant_Array[ant_row][ant_col] = '#';

			//check the boarder and move ant appropriately
			if ((ant_col + 1) == col)
			{
				ant_col = 0;
			}
			else
			{
				ant_col += 1;
			}

			//update color of the space at ant's new location if necessary
			if (ant_Array[ant_row][ant_col] == '#')
			{
				changeBoardColor();
			}

			//move ant marker
			ant_Array[ant_row][ant_col] = '*';
		}


		else if (getOrientation() == DOWN)
		{
			setOrientation(LEFT);

			ant_Array[ant_row][ant_col] = '#';


			if ((ant_col - 1) < 0)
			{
				ant_col = col - 1;
			}
			else
			{
				ant_col -= 1;
			}


			if (ant_Array[ant_row][ant_col] == '#')
			{
				changeBoardColor();
			}

			ant_Array[ant_row][ant_col] = '*';
		}


		else if (getOrientation() == LEFT)
		{
			
			setOrientation(UP);

			ant_Array[ant_row][ant_col] = '#';


			if ((ant_row - 1) < 0)
			{
				ant_row = row - 1;
			}
			else
			{
				ant_row -= 1;
			}


			if (ant_Array[ant_row][ant_col] == '#')
			{
				changeBoardColor();
			}

			ant_Array[ant_row][ant_col] = '*';
		}
		else
		{
			setOrientation(DOWN);

			ant_Array[ant_row][ant_col] = '#';


			if ((ant_row + 1) == row)
			{
				ant_row = 0;
			}
			else
			{
				ant_row += 1;
			}


			if (ant_Array[ant_row][ant_col] == '#')
			{
				changeBoardColor();
			}

			ant_Array[ant_row][ant_col] = '*';
		}
	}

	else if (board_Color == '#')
	{
		if (getOrientation() == UP)
		{
			setOrientation(LEFT);

			ant_Array[ant_row][ant_col] = ' ';


			if ((ant_col - 1) < 0)
			{
				ant_col = col - 1;
			}
			else
			{
				ant_col -= 1;
			}


			if (ant_Array[ant_row][ant_col] == ' ')
			{
				changeBoardColor();
			}

			ant_Array[ant_row][ant_col] = '*';
			
		}
		else if (getOrientation() == DOWN)
		{
			setOrientation(RIGHT);

			ant_Array[ant_row][ant_col] = ' ';


			if ((ant_col + 1) == col)
			{
				ant_col = 0;
			}
			else
			{
				ant_col += 1;
			}


			if (ant_Array[ant_row][ant_col] == ' ')
			{
				changeBoardColor();
			}

			ant_Array[ant_row][ant_col] = '*';
		}
		else if (getOrientation() == LEFT)
		{
			setOrientation(DOWN);

			ant_Array[ant_row][ant_col] = ' ';


			if ((ant_row + 1) == row)
			{
				ant_row = 0;
			}
			else
			{
				ant_row += 1;
			}

			if (ant_Array[ant_row][ant_col] == ' ')
			{
				changeBoardColor();
			}

			ant_Array[ant_row][ant_col] = '*';
		}
		else
		{
			setOrientation(UP);

			ant_Array[ant_row][ant_col] = ' ';


			if ((ant_row - 1) < 0)
			{
				ant_row = row - 1;
			}
			else
			{
				ant_row -= 1;
			}


			if (ant_Array[ant_row][ant_col] == ' ')
			{
				changeBoardColor();
			}

			ant_Array[ant_row][ant_col] = '*';
		}
	}
}


/**********************************************************
**Reverses the color of the space the ant is currently on.
***********************************************************/
void Ant::changeBoardColor()
{
	if (board_Color == ' ')
	{
		board_Color = '#';
	}
	else
	{
		board_Color = ' ';
	}
}


/*****************************************************
**Destructor that deallocates memory when the the ant
**object is destroyed
******************************************************/
Ant::~Ant()
{
	for (int i = 0; i < col; i++)
	{
		delete[] ant_Array[i];
	}

	delete[] ant_Array;

	ant_Array = NULL;
}
