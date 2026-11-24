#pragma once
#include "Player.h"
#include "Unit.h"
#include "Upgrade.h"
#include "Weapon.h"
#include <vector>

class Game
{
private:
	Player* player;
	int state = 0;
	// Menu: 0
	// Base = 1
	// Inventory = 2
	//Patrol = 3
	//Fight = 4

	std::vector<Unit> enemies;
};

