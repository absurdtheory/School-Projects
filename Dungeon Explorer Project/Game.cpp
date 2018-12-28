/****************************************************************************
**Program: Final Project
**Author: Alexis Tucker
**Date: 3/16/18
**Description: Functions for Game Class
*****************************************************************************/
#include "Game.hpp"

/***************************************************************************************
**Default constructor to initialize and allocate pointers
****************************************************************************************/
Game::Game()
{
	player1 = new Player();
	gameMap = new Map(player1);
}


/***************************************************************************************
**Menu function. Gives the user the option to quit or player the game. If the player 
**chooses to play, instructions are show on screen. Gives the player an option to 
**investigate a room, display inventory, use/drop an item, check current health, and 
**move rooms. Loops until player exits the dungeon or HP <= 0;
****************************************************************************************/
void Game::Menu()
{
	cout << endl;

	int select;

	cout << "Welcome to Cold Dungeon\n"
		<< "Please make a selection:\n"
		<< "1. Play		2. Quit" << endl;

	cin >> select;
	while (!inputValid(select) || select < 1 || select > 2)
	{
		cout << "Error: Please re-enter your selection." << endl;
		cin >> select;
	}
	
	if (select == 1)
	{
		cout << endl;
		cout << "You awaken in a dark, cold room.\n"
			<< "\nThe air seems strange... It's poisonous!\n"
			<< "You need to escape before you loose all your health...\n"
			<< "You will lose 1 point of health each time you move between rooms.\n"
			<< "\nThere must be a key somewhere in the dungeon to allow you to escape.\n"
			<< "Find the key and the exit!\n" << endl;

		cout << "Perhaps if you investigate the room you can find your way..." << endl;

		
		while (player1->getHP() > 0 && gameMap->getPlayer()->getOpenDoor() == false)
		{
			cout << endl;
			cout << gameMap->getPlayer()->getSpaceDesc() << endl;

			//forces player to investigate if Space is a TrapSpace
			if (gameMap->getPlayer()->getTrapSpace() == true)
			{
				gameMap->getPlayer()->investigate();
			}

			int choice = 0;

			while (choice != 5 && gameMap->getPlayer()->getOpenDoor() == false)
			{
				cout << endl;
				cout << "What would you like to do?\n"
					<< "1. Investigate			2. See Inventory\n"
					<< "3. Use/Drop an Item		4. Check Health\n"
					<< "5. Change rooms" << endl;


				cin >> choice;

				while (!inputValid(choice) || choice < 1 || choice > 5)
				{
					cout << "Error: Please re-enter your selection." << endl;
					cin >> choice;
				}

				if (choice == 1)
				{
					gameMap->getPlayer()->investigate();
				}

				else if (choice == 2)
				{
					player1->showInventory();
				}

				else if (choice == 3)
				{
					int udItem;
					int udItem2;

					//ask if use or drop and which item
					cout << "Would you like to use or drop an item?\n"
						<< "1. Use		2. Drop" << endl;

					cin >> udItem;

					while (!inputValid(udItem) || udItem > 2 || udItem < 1)
					{
						cout << "Error: Please re-enter selection." << endl;
						cin >> udItem;
					}

					cout << endl;

					if (player1->getInvSize() > 0)
					{
						player1->showInventory();

						cout << endl;

						cout << "Which item do you want to use or drop? (enter corresponding number)" << endl;

						cin >> udItem2;

						//loop until item found or error if not found
						while (!inputValid(udItem2) || udItem2 < 1 || udItem2 > player1->getInvSize())
						{
							cout << "Error: Please re-enter selection." << endl;
							cin >> udItem2;
						}

						if (udItem == 1)
						{
							if (player1->getItem(udItem2 - 1).getItemName() != "an eyeball")
							{
								Item drop = player1->getItem(udItem2 - 1);
								gameMap->getPlayer()->interact(drop);
							}

							else
							{
								player1->addHP(5);
								cout << "You consumed the eyeball and recovered some health." << endl;
								Item drop = player1->getItem(udItem2 - 1);
								player1->dropItem(drop);
							}
						}
						else
						{
							Item drop = player1->getItem(udItem2 - 1);
							if (drop.getItemName() == "a simple key")									//does not allow player to drop simple key
							{
								cout << "You cannot drop this, it seems very important." << endl;
							}
							else
							{
								player1->dropItem(drop);
								cout << drop.getItemName() << " was dropped." << endl;
							}
							
						}
					}
					else
					{
						cout << "Your inventory is empty..." << endl;
					}
				}

				else if (choice == 4)
				{
					cout << "Your current health is " << player1->getHP() << "." << endl;
				}

			}

			//if player uses the key to exit dungeon or dies, make sure they are not prompted to move again
			if (player1->getHP() > 0 && gameMap->getPlayer()->getOpenDoor() == false)
			{
				int move;
				bool validmove = false;

				while (validmove == false)
				{
					cout << "Which direction would you like to move\n"
						<< "1. North		2. South\n"
						<< "3. East			4. West" << endl;

					cin >> move;

					while (!inputValid(move) || move < 1 || move > 4)
					{
						cout << "Error: Please re-enter your selection." << endl;
						cin >> move;
					}

					validmove = gameMap->movePlayer(move);
				}
			}

			//check if player exits the dungeon and is not dead, if not
			if (player1->getHP() > 0 && gameMap->getPlayer()->getOpenDoor() == false)
			{
				player1->decHP();

			}
		}

		cout << endl;


		//displays if player wins/loses
		if (player1->getHP() <= 0)
		{
			cout << "You've succumbed to the dungeon!\n"
				<< "Game over!" << endl;
		}

		else
		{
			cout << "You've escaped the dungeon!\n"
				<< "You are victorious with " << player1->getHP() << " health remaining." << endl;
		}
	}

}

/***************************************************************************************
**Deallocate gameMap and player1
****************************************************************************************/
Game::~Game()
{
	//cout << "game destructor" << endl;
	delete gameMap;
	delete player1;
}