/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Header for class Game.
*********************************************************************************/
#ifndef GAME_HPP
#define GAME_HPP
#include "HarryPotter.hpp"
#include "Medusa.hpp"
#include "BlueMen.hpp"
#include "Vampire.hpp"
#include "Barbarian.hpp"
#include "Inputvalid.hpp"


class Game
{
private:

	struct TeamChar
	{
		BaseChar *fighter;
		TeamChar *next;
		TeamChar(BaseChar *fight1, TeamChar *next1 = NULL);
	};

	struct LoserChar
	{
		BaseChar *loser;
		LoserChar *prev;
		LoserChar(BaseChar *loser1, LoserChar *prev1 = NULL);
	};

	TeamChar *teamHead1 = NULL;
	TeamChar *teamHead2 = NULL;

	LoserChar *loserHead = NULL;

	int	score1,
		score2;

public:
	void Menu();												//Menu function that allows selection of characters and returns choice if to play again
	void rounds();											//loops until one of the teams loses
	void attack(TeamChar *head1, TeamChar *head2);			//first parameter attacks the second parameter, takes two TeamChar pointers


	//new functions
	void createTeam(int n);									//takes an integer n and creates two queue-like linked lists with n fighters
	void moveToBack(TeamChar *head);						//takes a TeamChar pointer, moves the fighter at the head of the queue to the back
	void moveToLoser(TeamChar *head);						//takes a TeamChar pointer, moves the fighter at the head of the queue to the loser pile
	void displayLoser();									//displays the loser list in a stack-like format
	void displayFinal();									//displays the final scores and the winner
	void clearQueue();										//deallocates the memory of the linked-lists

};


#endif