#pragma once
#include "Player.h"
#include "Unit.h"
#include "Upgrade.h"
#include "Weapon.h"
#include <vector>
#include <conio.h>

class Game
{
private:
	Player* player;
	// For state:
	// Menu: 0, Base = 1, Inventory = 2, Patrol = 3, Fight = 4
	int state = 0;
	//int difficulty = 1;
	//int score = 0;
	std::vector<Unit*> enemies;
	bool quit = false;
	
	void displayEnemies();

public:
	Game();
	~Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	void run();
	void mainMenu();
	void base();
	void inventory();
	void patrol();
	void fight();

	void gatherEnemies();
	void patrolChoice();


	void setPlayer(Player* p);

};

