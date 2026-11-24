#include "Game.h"

void Game::run()
{
	//Menu
	//Base
	//Inventory
	//Patrol
	//Fight
	while (!quit)
	{
		switch (state)
		{
		case 0 :
			std::cout << "========================================================\n";
			mainMenu();
			break;
		case 1:
			std::cout << "========================================================\n";
			base();
			break;
		case 2:
			std::cout << "========================================================\n";
			inventory();
			break;
		case 3:
			std::cout << "========================================================\n";
			gatherEnemies();
			patrolChoice();
			break;
		case 4:
			std::cout << "========================================================\n";
			fight();
			break;
		default:
			quit = true;
			break;
		}
	}
}

Game::Game()
{
	setPlayer(new Player());
}

Game::~Game()
{
	delete player;
	for (Unit* enemy : enemies)
	{
		delete enemy;
	}
}

void Game::displayEnemies()
{
	if (enemies.size() == 0)
	{
		std::cout << "No enemies present!\n";
		return;
	}
	int count = 0;
	for (Unit* enemy : enemies)
	{
		std::cout << "#" << count + 1 << ": " << enemy->getName() << "\n";
		count++;
	}
}

void Game::mainMenu()
{
	std::cout << "Welcome to the game, you will venture out and defeat enemies to upgrade your stats and wargear.\n"
		<< "Press C to continue, L to load, S to save, N for new save, Q to quit.\n"
		<< "Loading or New will continue to the game.\n";
	char input = _getch();
	if (input == 'C' || input == 'c')
	{
		std::cout << "========================================================\n";
		std::cout << "Continuing.\n";
		state = 1;
	}
	if (input == 'L' || input == 'l')
	{
		std::cout << "========================================================\n";
		std::cout << "Loading Player.\n";
		player->loadPlayer();
		state = 1;
	}
	if (input == 'S' || input == 's')
	{
		std::cout << "========================================================\n";
		std::cout << "Saving Player.\n";
		player->savePlayer();
	} 
	if (input == 'N' || input == 'n')
	{
		std::cout << "========================================================\n";
		std::cout << "New Player.\n";
		player = new Player();
		state = 1;
	} 
	if (input == 'Q' || input == 'q')
	{
		std::cout << "========================================================\n";
		std::cout << "Quitting game.\n";
		quit = true;
	}
}

void Game::base()
{
	std::cout << "In main base. Press I for Inventory, M to for Main Menu, P to start patrol, V to view your stats.\n"
		<< "Press S to rename yourself, W to rename your weapon.\n";
	char input = _getch();
	if (input == 'I' || input == 'i')
	{
		std::cout << "Checking inventory.\n";
		state = 2;
	}
	if (input == 'M' || input == 'm')
	{
		std::cout << "Going to main menu.\n";
		state = 0;
	}
	if (input == 'P' || input == 'p')
	{
		std::cout << "Going to Patrol.\n";;
		state = 3;
	}
	if (input == 'V' || input == 'v')
	{
		std::cout << "Viewing stats.\n";
		player->listStats();
	}
	if (input == 'S' || input == 's')
	{
		player->renameSelf();
	}
	if (input == 'W' || input == 'w')
	{
		player->renameWeapon();
	}
}

void Game::inventory()
{
	std::cout << "========================================================\n";
	if (player->listItems())
	{
		std::cout << "Enter the corresponding number to use an item, enter -1 to go to Base, -2 to go to Patrol.\n";
		int input;
		std::cin >> input;
		if (input > 0) player->useItem(input);
		if (input == -1) state = 1;
		if (input == -2) state = 3;
		std::cin.clear();
	}
	state = 1;
}

void Game::gatherEnemies()
{
	//Clear enemy vector first
	for (Unit* current : enemies)
	{
		delete current;
	}
	enemies.clear();
	for (int i = 0; i < player->getLevel(); i++)
	{
		int chance = rand() & 3;
		if (chance == 0) i++;
		enemies.push_back(Unit::unitFactory(player->getLevel()));
	}
}

void Game::patrolChoice()
{
	std::cout << "========================================================\n";
	std::cout << "You face the following enemies:\n";
	displayEnemies();
	std::cout << "Would you like to try and fight? F to fight, W to withdraw to base, I for inventory.\n";
	char input = _getch();
	if (input == 'F' || input == 'f')
	{
		std::cout << "Fighting!.\n";
		state = 4;
	}
	if (input == 'W' || input == 'w')
	{
		std::cout << "Withdrawing.\n";
		state = 1;
	}
	if (input == 'I' || input == 'i')
	{
		std::cout << "Checking inventory.\n";
		state = 2;
	}
}

void Game::fight()
{
	std::cout << "========================================================\n";
	std::cout << "Fighting " << enemies.size() << " Enemies!\n";
	std::cout << "Player will attack the a number of times corrosponding to their level, then every enemy will attack.\n"
		<< "This will continue until the player dies or there are no enemies left. Death will cause a level down.\n"
		<< "Good Luck!\n";
	std::cout << "=============================\n";
	int startHealth = player->getHealth();
	while (enemies.size() > 0)
	{
		for (int i = 0; i < player->getLevel(); i++)
		{
			player->attack(*enemies.back());
			if (!enemies.back()->isAlive())
			{
				std::cout << "Killed " << enemies.back()->getName() << "!\n";
				delete enemies.back();
				enemies.pop_back();
			}
			if (enemies.size() == 0) break;
		}
		if (enemies.size() != 0)
		{
			for (Unit* enemy : enemies)
			{
				enemy->attack(*player);
			}
		}
		if (!player->isAlive())
		{
			std::cout << "Player mortally wounded, tactically retreating to Base!\n";
			break;
		}
	}

	if (!player->isAlive())
	{
		player->setHealth(1);
		player->setAlive(true);
		player->levelDown();
	}
	else
	{
		player->levelUp();
		startHealth = startHealth - player->getHealth();
		player->addHealth(3);
		player->addUpgrade(Upgrade::randomUpgradeFactory());
		std::cout << "Enemies defeated, leveling up, healing and gaining random upgrade.\n"
			<< "You took " << startHealth << " damage.\n"
			<< "Your health: " << player->getHealth() << "\n";
	}
	state = 1;
}


void Game::setPlayer(Player* p)
{
	delete player;
	player = p;
}