/*******************************************************************************
**Program: Project 4
**Author: Alexis Tucker
**Date: 2/23/2018
**Description: Functions for Game Class
*********************************************************************************/
#include "Game.hpp"


/*****************************************************************
**Prompts the user to pick how many fighters on each team, dynamically 
**allocates those teams, calls rounds(), displays the winner, asks if
**user wants to see loser pile, asks user to play again loops until
**user chooses to quit
******************************************************************/
void Game::Menu()
{
	int select,
		numTeam,
		seeLoser;


	cout << "1. Play\n"
		<< "2. Exit\n";

	cin >> select;

	while (!inputValid(select) || select != 1 && select != 2)
	{
		cout << "Error: please re-enter your selection" << endl;
		cin >> select;
	}
	
	//while user chooses not to quite
	while (select != 2)
	{
		//prompt user for number of fighters on a team and create the teams
		cout << "How many fighters are on each team?\n";

		cin >> numTeam;

		while (!inputValid(numTeam) || numTeam < 1)
		{
			cout << "Error: please enter a integer greater than 0." << endl;
			cin >> numTeam;
		}

		createTeam(numTeam);

		
		//test teams were created correctly
		/*TeamChar *temp1,
			*temp2;

		temp1 = teamHead1;
		temp2 = teamHead2;

		cout << "team 1 start:" << endl;
		while (temp1 != NULL)
		{
			cout << temp1->fighter->getName() << endl;
			temp1 = temp1->next;
		}

		cout << "team 2 start: " << endl;
		while (temp2 != NULL)
		{
			cout << temp2->fighter->getName() << endl;
			temp2 = temp2->next;
		}
		*/


		//call rounds
		rounds();
		cout << endl;
		

		//display final scores and winner
		displayFinal();
		cout << endl;

		
		//ask if user wants to see losers and display them
		cout << "Do you want to see the contents of the loser pile?\n"
			<< "1. Yes\n"
			<< "2. No" << endl;

		cin >> seeLoser;

		while (!inputValid(seeLoser) || seeLoser != 1 && seeLoser != 2)
		{
			cout << "Error: please re-enter your selection" << endl;
			cin >> seeLoser;
		}

		if (seeLoser == 1)
		{
			displayLoser();
		}
		cout << endl;


		//ask if user wants to play again
		cout << "Game Over!\n"
			<< "Please select an option below.\n"
			<< "1. Play again\n"
			<< "2. Exit" << endl;

		cin >> select;

		while (!inputValid(select) || select != 1 && select != 2)
		{
			cout << "Error: please re-enter your selection" << endl;
			cin >> select;
		}

		//deallocate memory
		clearQueue();
	
	}
	//return;
}


/***********************************************************
**Displays the current round, the fighter from each team, and 
**the winner between them. Loops until one team has been 
**defeated. Moves losing fighter to loser pile and winning 
**fighter to back of the line-up
************************************************************/	
void Game::rounds()
{
	int round = 1;
	score1 = 0;
	score2 = 0;
	
	do
	{
		//team 1  fighter attacks team 2 fighter
		attack(teamHead1, teamHead2);
		
		//if team 2's fighter does not lose, attack team 1 fighter
		if(teamHead2->fighter->getStrength() > 0 || teamHead2->fighter->getSpecial() == HOGWARTS)
		{
			attack(teamHead2, teamHead1);
		
		}

		//if team 1's fighter loses
		if (teamHead1->fighter->getStrength() <= 0)
		{
			cout << endl;
			cout << "Round " << round << ": " << endl;
			score2++;
			round++;
			
			cout << "Team 2's " << teamHead2->fighter->getName() << ", " << teamHead2->fighter->getcharName()
				<< ", won against Team 1's " << teamHead1->fighter->getName() << ", " << teamHead1->fighter->getcharName() << endl;

			//move the loser to the loser pile
			moveToLoser(teamHead1);

			//move the winner to the back of the line-up
			moveToBack(teamHead2);

			//test teams
			/*
			TeamChar *temp1,
				*temp2;

			temp1 = teamHead1;
			temp2 = teamHead2;

			cout << "team 1 remaining:" << endl;
			while (temp1 != NULL)
			{
				cout << temp1->fighter->getName() << endl;
				temp1 = temp1->next;
			}

			cout << "team 2 remaining: " << endl;
			while (temp2 != NULL)
			{
				cout << temp2->fighter->getName() << endl;
				temp2 = temp2->next;
			}
			*/	
		}
		//else if team 2's fighter loses
		else if (teamHead2->fighter->getStrength() <= 0)
		{
			cout << endl;
			cout << "Round " << round << ": " << endl;

			score1++;
			round++;

			cout << "Team 1's " << teamHead1->fighter->getName() << ", " << teamHead1->fighter->getcharName()
				<< ", won against Team 2's "<< teamHead2->fighter->getName() << ", " << teamHead2->fighter->getcharName() << endl;

			//move loser to the loser pile
			moveToLoser(teamHead2);

			//move winner to the back of the line-up
			moveToBack(teamHead1);

			//test teams
			/*
			TeamChar *temp1,
				*temp2;

			temp1 = teamHead1;
			temp2 = teamHead2;

			cout << "team 1 remaining:" << endl;
			while (temp1 != NULL)
			{
				cout << temp1->fighter->getName() << endl;
				temp1 = temp1->next;
			}

			cout << "team 2 remaining: " << endl;
			while (temp2 != NULL)
			{
				cout << temp2->fighter->getName() << endl;
				temp2 = temp2->next;
			}
			*/
		}
	} while (teamHead1 != NULL && teamHead2 != NULL);			//loops until one team loses all fighters

}


/***********************************************************************
**Takes two TeamChar pointers, the first parameter attacks the second 
**parameter. Calls and checks for special attacks when appropriate. 
************************************************************************/
void Game::attack(TeamChar *head1, TeamChar *head2) 
{				
	if (!(head2->fighter->getSpecial() == CHARM && head2->fighter->specialAttack(head1->fighter) == true))										//if the attacker is not charmed
	{
		int attackR = head1->fighter->rollAttack();
		if (head1->fighter->getSpecial() != GLARE || (head1->fighter->getSpecial() == GLARE && head1->fighter->specialAttack(head2->fighter) == false))		//if the defender is not turned to stone
		{
			int defenseR = head2->fighter->rollDefense();
			int cArmor = head2->fighter->getArmor();

			head2->fighter->setDamage(attackR - defenseR - cArmor);															
			if (head2->fighter->getDamage() < 1)																				//if defense and armor are greater then attack, no damage taken
			{
				head2->fighter->setDamage(0);
			}
			
			//test attack
			/**
			cout << "The attacker, " << head1->fighter->getName() << ", rolled a total attack of " << attackR << endl;
			cout << "The defender, " << head2->fighter->getName() << ", has " << head2->fighter->getStrength() << " strength and rolled a total defense of " << defenseR
				<< " and has " << cArmor << " armor." << endl;
			*/
			
			//deduct any damage from defenders strength
			head2->fighter->setStrength(head2->fighter->getStrength() - head2->fighter->getDamage());

			//test defense
			
			cout << "The defender, " << head2->fighter->getName() << ", received " << head2->fighter->getDamage() << " points of damage and now has "
				<< head2->fighter->getStrength() << " strength." << endl;
			
			

			if (head2->fighter->getSpecial() == HOGWARTS || head2->fighter->getSpecial() == MOB)
			{
				head2->fighter->specialAttack(head1->fighter);
			}
		}
	}
}


/******************************************************************************************
**Constructor for struct TeamChar. Takes a BaseChar pointer to the fighter and a TeamChar 
**pointer to the next in the line-up
*******************************************************************************************/
Game::TeamChar::TeamChar(BaseChar *fight1, TeamChar *next1)
{
	fighter = fight1;
	next = next1; 
}


/******************************************************************************************
**Constructor for struct LoserChar. Takes a BaseChar pointer to the loser and a LoserChar
**pointer to the previous loserChar
*******************************************************************************************/
Game::LoserChar::LoserChar(BaseChar *loser1, LoserChar *prev1)
{
	loser = loser1;
	prev = prev1;
}


/******************************************************************************************
**Takes an integer and creates two teams with that number of fighters. Allows the user to 
**pick the type of fighter and give each fighter a name
*******************************************************************************************/
void Game::createTeam(int n)
{
	cout << "Pick the fighters for Team 1" << endl;


	for(int i = 1; i <= n; i++)
	{
		int pick;
		string name;
		BaseChar *char1;

		cout << endl;
		cout << "Characters available:\n"
			<< "1. Vampire \n"
			<< "2. Barbarian\n"
			<< "3. Blue Men\n"
			<< "4. Medusa \n"
			<< "5. Harry Potter" << endl;

		cin >> pick;

		while (!inputValid(pick) || pick < 1 || pick > 5)
		{
			cout << "Error: please re-enter your selection" << endl;
			cin >> pick;
		}

		//create character
		if (pick == 1)
		{
			char1 = new Vampire;
		}
		else if (pick == 2)
		{
			char1= new Barbarian;
		}
		else if (pick == 3)
		{
			char1 = new BlueMen;
		}
		else if (pick == 4)
		{
			char1 = new Medusa;
		}
		else if (pick == 5)
		{
			char1 = new HarryPotter;
		}

		cout << "What would you like to name fighter " << i << "?" << endl;

		cin >> name;

		char1->setcharName(name);

		if (teamHead1 == NULL)
		{
			teamHead1 = new TeamChar(char1);
		}
		else
		{
			TeamChar *fighterPtr = teamHead1;
			while (fighterPtr->next != NULL)
			{
				fighterPtr = fighterPtr->next;
			}
			fighterPtr->next = new TeamChar(char1);					
		}

	}

	cout << endl;
	cout << "Pick the fighters for Team 2" << endl;


	for (int i = 1; i <= n; i++)
	{
		int pick;
		string name;
		BaseChar *char1;

		cout << "Characters available:\n"
			<< "1. Vampire \n"
			<< "2. Barbarian\n"
			<< "3. Blue Men\n"
			<< "4. Medusa \n"
			<< "5. Harry Potter" << endl;

		cin >> pick;

		while (!inputValid(pick) || pick < 1 || pick > 5)
		{
			cout << "Error: please re-enter your selection" << endl;
			cin >> pick;
		}

		//create character
		if (pick == 1)
		{
			char1 = new Vampire;
		}
		else if (pick == 2)
		{
			char1 = new Barbarian;
		}
		else if (pick == 3)
		{
			char1 = new BlueMen;
		}
		else if (pick == 4)
		{
			char1 = new Medusa;
		}
		else if (pick == 5)
		{
			char1 = new HarryPotter;
		}

		cout << "What would you like to name fighter " << i << "?" << endl;

		cin.ignore();

		getline(cin, name);

		char1->setcharName(name);

		
		if (teamHead2== NULL)
		{
			teamHead2 = new TeamChar(char1);
		}
		else
		{
			TeamChar *fighterPtr = teamHead2;
			while (fighterPtr->next != NULL)
			{
				fighterPtr = fighterPtr->next;
			}
			fighterPtr->next = new TeamChar(char1);
		}

	}
}


/******************************************************************************************
**Moves the fighter at the front of the line-up to the back of the queue-like linked list. 
**Also calls recover so the fighter regenerates a random amount of strength
*******************************************************************************************/
void Game::moveToBack(TeamChar *head)															
{

	if (head != NULL)
	{
		if (head == teamHead1)
		{

			TeamChar *temp = teamHead1;

			teamHead1->fighter->recovery();

			while (temp->next != NULL)
			{
				temp = temp->next;
			}

			temp->next = teamHead1;

			teamHead1 = teamHead1->next;

			temp->next->next = NULL;

		}
		else
		{
			TeamChar *temp = teamHead2;

			teamHead2->fighter->recovery();

			while (temp->next != NULL)
			{
				temp = temp->next;
			}

			temp->next = teamHead2;

			teamHead2 = teamHead2->next;

			temp->next->next = NULL;

		}
	}
}


/******************************************************************************************
**Deletes the loser from the Line-up and adds it to the Loser pile which is a stack-like 
**linked list. The newest loser added to the list is at the head.
*******************************************************************************************/		
void Game::moveToLoser(TeamChar *head1)											
{
	if (head1 == teamHead1)
	{
		if (loserHead == NULL)
		{
			loserHead = new LoserChar(teamHead1->fighter);
		}
		else
		{
			loserHead = new LoserChar(teamHead1->fighter, loserHead);	
		}


		if (teamHead1->next == NULL)
		{
			delete teamHead1;
			teamHead1 = NULL;
		}
		else
		{
			TeamChar *temp = teamHead1;
			teamHead1 = teamHead1->next;
			delete temp;
		}
	}
	else
	{
		if (loserHead == NULL)
		{
			loserHead = new LoserChar(teamHead2->fighter);
		}
		else
		{
			loserHead = new LoserChar(teamHead2->fighter, loserHead);
		}

		if (teamHead2->next == NULL)
		{
			delete teamHead2;
			teamHead2 = NULL;
		}
		else
		{
			TeamChar *temp = teamHead2;
			teamHead2 = teamHead2->next;
			delete temp;
		}
	}
	
}

/************************************************************************************
**Traverses the loser pile. The last loser added is the first loser shown.
**************************************************************************************/
void Game::displayLoser()
{

	cout << "The content of the loser pile is: \n";
	
	LoserChar *temp = loserHead;
	
	
	while (temp != NULL)
	{
		cout << temp->loser->getcharName() << ", a " << temp->loser->getName() << endl;
		temp = temp->prev;
	}
	
}


/******************************************************************************************
**Displays the final scores and which team won.
*******************************************************************************************/
void Game::displayFinal()
{
	cout << "The final scores are:\n"
		<< "Team 1: " << score1 << "\n"
		<< "Team 2: " << score2 << endl;
	
	if (score1 == score2)
	{
		cout << "The tournament was a tie!" << endl;
	}
	else if (score1 > score2)
	{
		cout << "Team 1 wins the tournament!" << endl;
	}
	else
	{
		cout << "Team 2 wins the tournament!" << endl;
	}
}


/******************************************************************************************
**Deallocates all queues/stack that are not currently empty.
*******************************************************************************************/
void Game::clearQueue()
{
	if (teamHead1)
	{
		while (teamHead1 != NULL)
		{
			TeamChar *deletePtr = teamHead1;

			teamHead1 = teamHead1->next;

			delete deletePtr->fighter;
			delete deletePtr;

		}	
	}

	if(teamHead2)
	{
		while (teamHead2 != NULL)
		{
			TeamChar *deletePtr = teamHead2;

			teamHead2 = teamHead2->next;

			delete deletePtr->fighter;
			delete deletePtr;
		}
	}


	if(loserHead)
	{
		while (loserHead != NULL)
		{
			LoserChar *deletePtr = loserHead;

			loserHead = loserHead->prev;

			delete deletePtr->loser;
			delete deletePtr;
		}
	}

}
