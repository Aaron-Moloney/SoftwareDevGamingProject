#include "Player.h"
#include <string>

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
	//inventory.push_back(new HealthBuff);
	//inventory.push_back(new HealthBuff);
	//inventory.push_back(new HealthBuff);
}

Player::~Player()
{
	//std::cout << "Deleting inventory items.";
	for (Upgrade* item : inventory)
	{
		delete item;
	}
}

bool Player::listItems()
{
	if (inventory.size() == 0)
	{
		std::cout << "Inventory empty.\n";
		return false;
	}
	std::cout << "Displaying inventory, press I again to leave, press the corrosponding number to use an item:\n";
	int count = 0;
	for (Upgrade* current : inventory)
	{
		std::cout << "#" << count + 1 << ": " << current->getName() << "\n";
		count++;
	}
	return true;
}

void Player::useItem(int item)
{
	item--;
	if (item < inventory.size() && item >= inventory.size())
	{
		std::cout << "Invalid input.\n";
		return;
	}
	//int location = item - 1;
	inventory[item]->useUpgrade(*this);
	delete inventory[item];
	inventory.erase(inventory.begin() + item);
}

//int Player::getXp() const
//{
//	return xp;
//}
//void Player::setXp(int newXp)
//{
//	if (newXp <= 0)
//	{
//		xp = 1;
//		return;
//	}
//	xp = newXp;
//}
//void Player::addXp(int newXp)
//{
//	setXp(getXp() + newXp);
//}

int Player::getLevel() const
{
	return level;
}
void Player::setLevel(int newLevel)
{
	if (newLevel <= 0)
	{
		level = 1;
		return;
	}
	level = newLevel;
}
void Player::levelUp()
{
	setLevel(getLevel() + 1);
}
void Player::levelDown()
{
	setLevel(getLevel() - 1);
}

//int Player::getXpNeeded() const
//{
//	return xpNeeded;
//}
//void Player::setXpNeeded(int newNeeded)
//{
//	if (newNeeded <= 0)
//	{
//		xpNeeded = 1;
//		return;
//	}
//	xpNeeded = newNeeded;
//}
//void Player::increaseXpNeeded(int newNeeded)
//{
//	setXpNeeded(getXpNeeded() + newNeeded);
//}

int Player::getKills()
{
	return kills;
}
void Player::setKills(int newKills)
{
	if (newKills > -1)
	{
		kills = newKills;
		return;
	}
	kills = 0;
}
void Player::incrementKills()
{
	setKills(getKills() + 1);
}

void Player::savePlayer() const
{
	std::ofstream file("playerSave.txt");

	//Name
	file << getName() << '\n';

	//Characteristics
	file << isAlive() << ' ' << getMaxHealth() << ' ' << getHealth() << ' '
		<< getSave() << ' ' << getInSv() << ' ' << getToughness() << ' ' << getWeaponSkill() << '\n';

	//Level stats
	file << getLevel() << '\n';

	//Inventory
	file << inventory.size() << '\n';
	for (Upgrade* item : inventory)
		file << item->getName() << '\n';
	//For weapon, have to create a custom weapon when loading the player to account for upgrades.
	if (getWeapon())
	{
		file << getWeapon()->getName() << '\n';
		file << getWeapon()->getShots() << ' ' << getWeapon()->getDamage()
			<< ' ' << getWeapon()->getAp() << ' ' << getWeapon()->getStrength() << ' ' << getWeapon()->isSustained()
			<< ' ' << getWeapon()->isLethal() << ' ' << getWeapon()->isDevastating();
	}
	else
	{
		file << "emptyWeapon" << "\n";
	}
	
}
void Player::loadPlayer()
{
	std::ifstream file("playerSave.txt");
	if (!file)
	{
		std::cout << "No save present, create new save instead.\n";
		return;
	}
	
	std::string name;
	bool alive;
	int maxHealth, health, save, invSv, toughness, weaponSkill;
	int xp, level, xpNeeded;
	file >> name >> alive >> maxHealth >> health>> save >> invSv >> toughness >> weaponSkill >> xp >> level >> xpNeeded;

	setName(name);
	setAlive(alive);
	setMaxHealth(maxHealth);
	setHealth(health);
	setSave(save);
	setInSv(invSv);
	setToughness(toughness);
	setWeaponSkill(weaponSkill);
	//setXp(xp);
	setLevel(level);
	//setXpNeeded(xpNeeded);

	int inventorySize;
	file >> inventorySize;
	file.ignore();

	//Clear inventory to overwrite from save
	for (Upgrade* current : inventory)
	{
		delete current;
	}
	inventory.clear();
	
	for (int i = 0; i < inventorySize; i++)
	{
		std::string name;
		std::getline(file, name);
		Upgrade* newUpgrade = Upgrade::upgradeFactory(name);
		if (newUpgrade) inventory.push_back(newUpgrade);
	}

	int shots, damage, ap, strength;
	bool sustained, lethal, devastating;

	std::string weaponName;
	std::getline(file, weaponName);

	if (weaponName != "emptyWeapon")
	{
		file >> shots >> damage >> ap >> strength;
		file >> sustained >> lethal >> devastating;
		Weapon* newWeapon = new CustomWeapon(weaponName, shots, damage, ap, strength, sustained, lethal, devastating);
		setWeapon(newWeapon);
	}
	else
	{
		//Default to bolter
		setWeapon(new Bolter());
	}
}

void Player::listStats()
{
	std::cout << "========================================================\n";
	std::cout << " | Level: " << getLevel() << "\n";
	printDetails();
	std::cout << "Weapon details:\n";
	getWeapon()->printDetails();
}

void Player::renameSelf()
{
	std::cout << "Renaming self, enter a new name: \n";
	std::string newName;
	std::cin >> newName;
	if (newName.length() > 0)
	{
		setName(newName);
		return;
	}
}
void Player::renameWeapon()
{
	std::cout << "Renaming weapon, enter a new name: \n";
	std::string newName;
	std::cin >> newName;
	if (newName.length() > 0)
	{
		getWeapon()->setName(newName);
		return;
	}
}

void Player::addUpgrade(Upgrade* u)
{
	inventory.push_back(u);
}