#pragma once

#include <vector>
#include <iostream>
#include "Unit.h"
#include "Upgrade.h"

class Player : public Unit
{
private:
	std::vector<Upgrade*> inventory;
	int xp = 0;
	int level = 1;
	int xpToLevel;
public:
	Player();
	~Player();
	void listItems();

	void useItem(int item);
};

