#include "Upgrade.h"


std::string GunBuff::getName() const { return "Gun Buff"; }

void GunBuff::useUpgrade(Unit& unit) const
{
	int upgradeType = rand() % 5;
	if (upgradeType == 4) upgradeType = rand() % 5;
	switch (upgradeType)
	{
	case 0:
		unit.getWeapon()->addDamage();
		std::cout << "Improved weapon damage.\n";
		break;
	case 1:
		unit.getWeapon()->addShots();
		std::cout << "Improved weapon shots.\n";
		break;
	case 2:
		unit.getWeapon()->addAp();
		std::cout << "Improved weapon ap.\n";
		break;
	case 3:
		unit.getWeapon()->addStrength();
		std::cout << "Improved weapon strength.\n";
		break;
	case 4:
		unit.getWeapon()->buffAll();
		std::cout << "Improved all weapon stats.\n";
		break;
	default:
		break;
	}
}

std::string UnitBuff::getName() const { return "Unit Buff"; }

void UnitBuff::useUpgrade(Unit& unit)const
{
	//InSv is very powerful so we filter it and others to be less likely, boosting maxhealth is the most likely
	int upgradeType = rand() % 5;
	if (upgradeType == 2) upgradeType = rand() % 5;
	if (upgradeType == 2) upgradeType = rand() % 5;
	if (upgradeType == 2 || upgradeType == 3) upgradeType = rand() % 5;
	if (upgradeType == 2 || upgradeType == 3 || upgradeType == 4) upgradeType = rand() % 5;
	if (upgradeType == 1 || upgradeType == 2 || upgradeType == 3 || upgradeType == 4) upgradeType = rand() % 5;
	switch (upgradeType)
	{
	case 0:
		unit.addMaxHealth();
		unit.setHealth(unit.getMaxHealth());
		std::cout << "Improved unit health.\n";
		break;
	case 1:
		unit.improveSave();
		std::cout << "Improved unit save.\n";
		break;
	case 2:
		unit.improveInSv();
		std::cout << "Improved unit invulnerable save.\n";
		break;
	case 3:
		unit.improveToughness();
		std::cout << "Improved unit toughness.\n";
		break;
	case 4:
		unit.imrpoveWeaponSkill();
		std::cout << "Improved unit weapon skill.\n";
		break;
	default:
		break;
	}
}

std::string HealthBuff::getName() const
{
	return "Health buff";
}

void HealthBuff::useUpgrade(Unit& unit) const
{
	std::cout << "Improved health by 3.\n";
	unit.setMaxHealth(unit.getMaxHealth() + 3);
	unit.setHealth(unit.getMaxHealth());
}

std::string ShotBuff::getName() const
{
	return "Shot buff";
}

void ShotBuff::useUpgrade(Unit& unit) const
{
	std::cout << "Improving shots by 2.\n";
	unit.getWeapon()->addShots(2);
}

std::string Heal::getName() const
{
	return "Heal";
}

void Heal:: useUpgrade(Unit& unit) const
{
	int healAmount = 3 + (rand() % unit.getMaxHealth());
	std::cout << "Healing " << healAmount << " health.\n";
	unit.addHealth(healAmount);
}