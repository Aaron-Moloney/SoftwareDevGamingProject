#include "Player.h"

Player::Player()
{
	setName("Player");
	setMaxHealth(8);
	setHealth(6);
	setSave(4);
	setInSv(6);
	setToughness(5);
	setWeaponSkill(4);
	setWeapon(new Bolter);
	inventory.push_back(new HealthBuff);
	inventory.push_back(new HealthBuff);
	inventory.push_back(new HealthBuff);
}

void Player::listItems()
{
	{
		if (inventory.size() == 0)
		{
			std::cout << "Inventory empty.\n";
			return;
		}
		std::cout << "Displaying inventory, press I again to leave, press the corrosponding number to use an item:\n";
		int count = 0;
		for (Upgrade* current : inventory)
		{
			std::cout << "#" << count + 1 << ": " << current->getName() << "\n";
			count++;
		}
	}
}

void Player::useItem(int item)
{
	if (item > inventory.size() || item < inventory.size()) return;
	int location = item - 1;
	inventory[location]->useUpgrade(*this);
}