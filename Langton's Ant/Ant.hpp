/*************************************************************************
**Program Name: Project 1
**Author: Alexis Tucker
**Date: 1/17/2018
**Description: Header for ant class that defines private and public class 
**members and enum. Descriptions below.
**************************************************************************/
#ifndef ANT_HPP
#define ANT_HPP

enum Orient { UP, DOWN, LEFT, RIGHT };						  //enum that shows the direction the ant is facing

class Ant
{
	private:
		char **ant_Array;										//pointer to 2D array
		int	row,												//number of rows in array
			col,												//number of columns in array
			ant_row,											//ant's starting row
			ant_col;											//ant's starting column									
		Orient orientation;										//enum variable that holds the ant's orientation	
		char board_Color;										//variable the holds the color of the space the ant is currently on

	public:
		Ant(int, int, int, int, Orient);						//constructor that creates a 2D array and places ant on the board facing a specified direction
		void setOrientation(Orient);							//function that takes the enum variable and changes the direction the ant is facing to it
		Orient getOrientation();								//function that returns the direction the ant is facing
		void printBoard();										//prints the board on the screen
		void moveAnt();											//moves the ant according to its direction and the color of the space it is one
		void changeBoardColor();								//reverses the color of board_Color
		~Ant();													//deconstructor that deallocated memory
};

#endif