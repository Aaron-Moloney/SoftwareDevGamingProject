#include "Unit.h"
#include <iostream>

Unit::Unit()
{

}
//Delets the weapon to free memory
Unit::~Unit()
{
	//std::cout << "Deleting " << weapon->getName() << "\n";
	delete weapon;
};
//Returns true if dice rolls equal or greater than input
bool Unit::diceHigher(int value)
{
	return value <= (rand() % 6) + 1;
}
//Returns true if dice rolls equal or greater than inputs, dice rolled outside of method
bool Unit::diceHigher(int value, int roll)
{
	return value <= roll;
}
//Rolls a dice
int Unit::rollDice()
{
	return (rand() % 6) + 1;
}

//Game logic to determine value needed during wound roll
//Please refer to the Core Rules for Warhammer 40,000
int Unit::woundValue(int value)
{
	if (weapon->getStrength() >= 2 * value) return 2;
	else if (weapon->getStrength() > value) return 3;
	else if (weapon->getStrength() == value) return 4;
	else if (weapon->getStrength() < value)
	{
		if (weapon->getStrength() <=  value / 2) return 6;
	}
	return 5;
}

//Attack sequence logic
//Please refer to the Core Rules for Warhammer 40,000 for further explanation
//In short, dice must beat or match roll requirements eg. 4 for weaponskills
//Then the defending unit must not fail the save roll.
//Weapon modifiers bypass these to some degrees
bool Unit::attack(Unit& target)
{
	int sustainedCount = 0;
	//std::cout << getWeapon()->getShots();
	//Time to roll dice
	for (int i = 0; i < getWeapon()->getShots(); i++)
	{
		//std::cout << "Shot number: " << i + 1 << "\n";
		//Roll to hit
		int hitRoll = rollDice();
		int woundRoll = rollDice();
		if (diceHigher(getWeaponSkill(), hitRoll))
		{
			//std::cout << "Hit.\n";
			//If lethal and 6 skip wound step
			if (hitRoll == 6)
			{
				if (getWeapon()->isSustained()) sustainedCount++;
				if (getWeapon()->isLethal())
				{
					if (diceHigher(getSaveAfterAp(getWeapon()->getAp())))
					{
						target.takeHealth(getWeapon()->getDamage());
						//std::cout << "Failed save.\n";
					}
				}
			}
			
			else if (diceHigher(woundValue(target.getToughness()), woundRoll))
			{
				//std::cout << "Wound.\n";
				//Devastating skips save rolls on a 6 to wound.
				if (getWeapon()->isDevastating() && woundRoll == 6)
				{
					target.takeHealth(getWeapon()->getDamage());
					//std::cout << "Dev wound.\n";
				}
				if (diceHigher(getSaveAfterAp(getWeapon()->getAp())))
				{
					target.takeHealth(getWeapon()->getDamage());
					//std::cout << "Failed save.\n";
				}
			}
		}
	}
	//std::cout << "Sustained hit count: " << sustainedCount << "\n";
	for (int j = 0; j < sustainedCount; j++)
	{
		int woundRoll = rollDice();
		if (diceHigher(woundValue(target.getToughness()), woundRoll))
		{
			//std::cout << "Wound.\n";
			//Devastating skips save rolls on a 6 to wound.
			if (getWeapon()->isDevastating() && woundRoll == 6)
			{
				target.takeHealth(getWeapon()->getDamage());
				//std::cout << "Dev wound.\n";
				break;
			}
			if (diceHigher(getSaveAfterAp(getWeapon()->getAp())))
			{
				target.takeHealth(getWeapon()->getDamage());
				//std::cout << "Failed save.\n";
				break;
			}
		}
	}
	return target.isAlive();
}

//Prints unit details
void Unit::printDetails()
{
	std::cout << "Name: " << name << " | MaxHealth: " << maxHealth << " | Health: " << health << " | Save: " << save << " | InvSv: " << invSv
		<< " | Toughness: " << toughness << " | WeaponSkill: " << weaponSkill << " | Weapon: " << weapon->getName() << "\n";
}

//Getters and setters
bool Unit::isAlive() const { return alive; };
void Unit::setAlive(bool newAlive) { alive = newAlive; }
//Simple kill function, called if an attack would drop health below 0
void Unit::kill()
{
	setHealth(0);
	alive = false;
}

//Many getters, setters and incrementers, accounts for invalid values according to game logic
std::string Unit::getName() const { return name; }
void Unit::setName(std::string newName) { name = newName; }

int Unit::getHealth() const { return health; }
void Unit::setHealth(int newHealth) { newHealth < 0 ? health = 0 : (newHealth > getMaxHealth() ? health = getMaxHealth() : health = newHealth); }
void Unit::addHealth(int heal) { heal > 0 ? setHealth(getHealth() + heal) : setHealth(getHealth()); } //Redundant expression to appease compiler
void Unit::takeHealth(int damage) { damage < 0 ? setHealth(getHealth()) : (getHealth() - damage < 1 ? kill() : setHealth(getHealth() - damage)); }
void Unit::healFull() { setHealth(getMaxHealth()); }

int Unit::getMaxHealth() const { return maxHealth; }
void Unit::setMaxHealth(int newMaxHealth) { newMaxHealth < 1 ? maxHealth = 1 : maxHealth = newMaxHealth; }
void Unit::addMaxHealth(int addMax) { addMax > 0 ? setMaxHealth(getMaxHealth() + addMax) : setMaxHealth(getMaxHealth()); } //Redundant expression to appease compiler
void Unit::takeMaxHealth(int decreaseMax ) { decreaseMax > 0 ? setMaxHealth(getMaxHealth() - decreaseMax) : setMaxHealth(getMaxHealth()); }

int Unit::getSave() const { return save; }
//Can't be lower than 2 as that would be unfailable in a D6 based game.
void Unit::setSave(int newSave) { newSave < 2 ? save = 2 : (newSave > 7 ? save = 7 : save = newSave); }
//Higher values for save are worse in this game, only ever increment or decrement them by 1
void Unit::worsenSave() { setSave(getSave() + 1); }
void Unit::improveSave() { setSave(getSave() - 1); }

int Unit::getInSv() const { return invSv; }
void Unit::setInSv(int newInvSv) { newInvSv < 2 ? invSv = 2 : (newInvSv > 7 ? invSv = 7 : invSv = newInvSv); }
//Higher values for save are worse in this game, only ever increment or decrement them by 1
void Unit::worsenInSv() { setInSv(getInSv() + 1); }
void Unit::improveInSv() { setInSv(getInSv() - 1); }

//Save cant be worse than insv after mods so return the best of the 2
int Unit::getSaveAfterAp(int ap)
{
	if (this->getSave() + ap > this->getInSv()) return this->getInSv();
	else return this->getSave() + ap;
}

int Unit::getToughness() const { return toughness; }
void Unit::setToughness(int newToughness) { newToughness > 0 ? toughness = newToughness : toughness = 1; }
void Unit::worsenToughness(int debuff) { debuff > 0 ? setToughness(getToughness() - debuff) : setToughness(getToughness()); }
void Unit::improveToughness(int buff) { buff > 0 ? setToughness(getToughness() + buff) : setToughness(getToughness()); }

int Unit::getWeaponSkill() const { return weaponSkill; }
//Ensure values are between 2 and 6 inclusive
void Unit::setWeaponSkill(int newWeaponSkill) { newWeaponSkill < 2 ? weaponSkill = 2 : (newWeaponSkill > 6 ? weaponSkill = 6 : weaponSkill = newWeaponSkill); }
//Higher values for save are worse in this game, only ever increment or decrement them by 1
void Unit::worsenWeaponSkill() { setWeaponSkill(getWeaponSkill() + 1); }
void Unit::imrpoveWeaponSkill() { setWeaponSkill(getWeaponSkill() - 1); }

Weapon* Unit::getWeapon() const { return weapon; }
void Unit::setWeapon(Weapon* newWeapon)
{
	delete weapon;
	weapon = newWeapon;
}
//Free memory
void Unit::deleteWeapon()
{
	delete weapon;
	weapon = nullptr;
}

//Buff stats
void Unit::buffUnit()
{
	addMaxHealth(4);
	healFull();
	improveToughness();
	improveSave();
	imrpoveWeaponSkill();
}

void Unit::buffAllUnit()
{
	buffUnit();
	weapon->buffAll();
}

//Returns a unit based on the players level
//Randomly chooses also
Unit* Unit::unitFactory(int level)
{
	if (level < 3) return new GuardsMan();
	if (level < 5)
	{
		int chance = rand() % 3;
		if (chance == 0)  return new SpaceMarine();
		else return new GuardsMan();
	}
	if (level < 8)
	{
		int chance = rand() % 3;
		if (chance == 0)  return new GuardsMan();
		else return new SpaceMarine();
	}
	if (level < 10) return new SpaceMarine();
	if (level < 12)
	{
		int chance = rand() % 3;
		if (chance == 0)  return new Eradicator();
		else return new SpaceMarine();
	}
	if (level < 15)
	{
		int chance = rand() % 5;
		if (chance == 0)  return new Eradicator();
		else if (chance == 1)  return new Hellblaster();
		else if (chance == 2)  return new Eliminator();
		else if (chance == 3)  return new Devastator();
		else return new SpaceMarine();
	}
	if (level < 30)
	{
		int chance = rand() % 6;
		if (chance == 0)  return new Eradicator();
		else if (chance == 1)  return new Hellblaster();
		else if (chance == 2)  return new Eliminator();
		else if (chance == 3)  return new Devastator();
		else if (chance == 4) return new Terminator();
		else return new SpaceMarine();
	}
	int chance = rand() % 6;
	if (chance == 0)  return new Terminator();
	else if (chance == 1)  return new Hellblaster();
	else if (chance == 2)  return new Terminator();
	else if (chance == 3)  return new Devastator();
	else if (chance == 4) return new Terminator();
	else return new Terminator();
}