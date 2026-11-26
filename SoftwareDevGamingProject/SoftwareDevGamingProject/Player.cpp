#include "Player.h"
#include <string>

//Default player stats
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
}

//Clears inventory and frees memory, Unit handles the weapon
Player::~Player()
{
	//std::cout << "Deleting inventory items.";
	for (Upgrade* item : inventory)
	{
		delete item;
	}
}

//Lists all items held in inventory, says if empty
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

//Uses the item at the location given, then deletes the item to free the memory and resizes the vector
void Player::useItem(int item)
{
	item--;
	if (item < inventory.size() || item >= inventory.size())
	{
		std::cout << "Invalid input.\n";
		return;
	}
	//int location = item - 1;
	inventory[item]->useUpgrade(*this);
	delete inventory[item];
	inventory.erase(inventory.begin() + item);
}

//Getter
int Player::getLevel() const
{
	return level;
}
//Setter, accounts for minimum allowed level
void Player::setLevel(int newLevel)
{
	if (newLevel <= 0)
	{
		level = 1;
		return;
	}
	level = newLevel;
}
//Increments level
void Player::levelUp()
{
	setLevel(getLevel() + 1);
}
//Decrements level
void Player::levelDown()
{
	setLevel(getLevel() - 1);
}

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

//Saves the players stats and weapon stats to a file
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
//Updates the players stats based on whats read from the files.
//Must construct a custom weapon as upgrades will mean there's no template to choose from
void Player::loadPlayer()
{
	std::ifstream file("playerSave.txt");
	if (!file)
	{
		std::cout << "No save present, create a new save instead.\n";
		return;
	}
	
	std::string name;
	bool alive;
	int maxHealth, health, save, invSv, toughness, weaponSkill;
	int xp, level, xpNeeded;
	file >> name >> alive >> maxHealth >> health>> save >> invSv >> toughness >> weaponSkill >> level;

	setName(name);
	setAlive(alive);
	setMaxHealth(maxHealth);
	setHealth(health);
	setSave(save);
	setInSv(invSv);
	setToughness(toughness);
	setWeaponSkill(weaponSkill);
	setLevel(level);

	int inventorySize;
	file >> inventorySize;
	file.ignore();

	//Clear inventory to overwrite from save
	for (Upgrade* current : inventory)
	{
		delete current;
	}
	inventory.clear();
	
	//Add items based on name in file
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

	//Create custom weapon using params
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

//Lists players level, stats and weapon stats
void Player::listStats()
{
	std::cout << "========================================================\n";
	std::cout << "Level: " << getLevel() << "\n";
	printDetails();
	std::cout << "Weapon details:\n";
	getWeapon()->printDetails();
}

//Renames player if valid input
void Player::renameSelf()
{
	std::cout << "Renaming self, enter a new name: \n";
	std::string newName;
	std::cin >> newName;
	if (newName.length() > 0)
	{
		setName(newName);
		std::cin.clear();
		return;
	}
}
//Renames weapon if valid input
void Player::renameWeapon()
{
	std::cout << "Renaming weapon, enter a new name: \n";
	std::string newName;
	std::cin >> newName;
	if (newName.length() > 0)
	{
		getWeapon()->setName(newName);
		std::cin.clear();
		return;
	}
}
//Adds an upgrade to the inventory
void Player::addUpgrade(Upgrade* u)
{
	inventory.push_back(u);
}