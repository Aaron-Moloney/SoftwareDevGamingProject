#include "Upgrade.h"


std::string GunBuff::getName() const { return "Gun Buff"; }

void GunBuff::useUpgrade(Unit& unit) const
{
	int upgradeType = rand() % 8;
	if (upgradeType == 4) upgradeType = rand() % 5;
	bool success = false;
	if (!success)
	{
		switch (upgradeType)
		{
		case 0:
			unit.getWeapon()->addDamage();
			std::cout << "Improved weapon damage.\n";
			success = true;
			break;
		case 1:
			unit.getWeapon()->addShots();
			std::cout << "Improved weapon shots.\n";
			success = true;
			break;
		case 2:
			unit.getWeapon()->addAp();
			std::cout << "Improved weapon ap.\n";
			success = true;
			break;
		case 3:
			unit.getWeapon()->addStrength();
			std::cout << "Improved weapon strength.\n";
			success = true;
			break;
		case 4:
			unit.getWeapon()->buffAll();
			std::cout << "Improved all weapon stats.\n";
			success = true;
			break;
		case 5:
			if (!unit.getWeapon()->isLethal())
			{
				unit.getWeapon()->setLethal(true);
				std::cout << "Weapon is lethal.\n";
				success = true;
			}
			break;
		case 6:
			if (!unit.getWeapon()->isSustained())
			{
				unit.getWeapon()->setSustained(true);
				std::cout << "Weapon is sustained.\n";
				success = true;
			}
			break;
		case 7:
			if (!unit.getWeapon()->isDevastating())
			{
				unit.getWeapon()->setDevastating(true);
				std::cout << "Weapon is devastating.\n";
				success = true;
			}
			break;
		default:
			break;
		}
	}
	
}

std::string UnitBuff::getName() const { return "Unit Buff"; }

void UnitBuff::useUpgrade(Unit& unit)const
{
	//InSv is very powerful so we filter it and others to be less likely, boosting maxhealth is the most likely
	//some stats can reach maximums, reroll if so
	while (true)
	{
		int upgradeType = rand() % 8;
		if (upgradeType == 1)
		{
			if (unit.getInSv() > 2)
			{
				unit.improveInSv();
				std::cout << "Improved unit invulnerable save.\n";
			}
		}
		else if (upgradeType == 2 || upgradeType == 3)
		{
			unit.improveToughness();
			std::cout << "Improved unit toughness.\n";
		}
		else if (upgradeType == 3 || upgradeType == 4 || upgradeType == 5)
		{
			if (unit.getWeaponSkill() > 2)
			{
				unit.imrpoveWeaponSkill();
				std::cout << "Improved unit weapon skill.\n";
				break;
			}
		}
		else
		{
			if (unit.getSave() > 2)
			{
				unit.improveSave();
				std::cout << "Improved unit save.\n";
				break;
			}
		}
	}
}

std::string HealthBuff::getName() const
{
	return "Health Buff";
}

void HealthBuff::useUpgrade(Unit& unit) const
{
	std::cout << "Improved health by 3.\n";
	unit.setMaxHealth(unit.getMaxHealth() + 2);
	unit.setHealth(unit.getMaxHealth());
}

std::string ShotBuff::getName() const
{
	return "Shot Buff";
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

Upgrade* Upgrade::upgradeFactory(const std::string& upgrade)
{
	if (upgrade == "Gun Buff") return new GunBuff();
	if (upgrade == "Unit Buff") return new UnitBuff();
	if (upgrade == "Health Buff") return new HealthBuff();
	if (upgrade == "Shot Buff") return new ShotBuff();
	if (upgrade == "Heal") return new Heal();
	//Return heal by default
	return new Heal();
}

Upgrade* Upgrade::randomUpgradeFactory()
{
	int random = rand() % 4;
	if (random == 0) return new GunBuff();
	if (random == 1) return new UnitBuff();
	if (random == 2) return new ShotBuff();
	if (random == 3) return new HealthBuff();
	//Return heal by default
	return new Heal();
}