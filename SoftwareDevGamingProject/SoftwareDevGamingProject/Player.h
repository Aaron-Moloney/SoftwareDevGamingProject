#pragma once

#include <vector>
#include <iostream>
#include "Unit.h"
#include "Upgrade.h"
#include <fstream>

class Player : public Unit
{
private:
	std::vector<Upgrade*> inventory;
	//int xp = 0;
	int level = 1;
	//int xpNeeded = 5;
	int kills = 0;

public:
	Player();
	~Player();
	bool listItems();

	void useItem(int item);

	//int getXp() const;
	//void setXp(int newXp);
	//void addXp(int newXp);

	int getLevel() const;
	void setLevel(int newLevel);
	void levelUp();
	void levelDown();
	
	//int getXpNeeded() const;
	//void setXpNeeded(int newNeeded);
	//void increaseXpNeeded(int newNeeded);

	int getKills();
	void setKills(int newKills);
	void incrementKills();

	void savePlayer() const;
	void loadPlayer();

	void listStats();

	void renameSelf();
	void renameWeapon();

	void addUpgrade(Upgrade* u);
};

