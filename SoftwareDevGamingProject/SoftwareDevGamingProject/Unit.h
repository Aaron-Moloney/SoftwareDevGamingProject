#pragma once

#include <iostream>
#include "Weapon.h"

class Unit
{
private:
	bool alive = true;
	std::string name = "Unit";
	int health = 1;
	int maxHealth = health;
	int save = 6;
	int invSv = 7;
	int toughness = 3;
	int weaponSkill = 5;
	Weapon* weapon = nullptr;
public:
	Unit();
	~Unit();

	bool diceHigher(int value);
	bool diceHigher(int value, int roll);
	int rollDice();
	int woundValue(int value);
	bool attack(Unit& target);

	void printDetails();

	bool isAlive() const;
	void setAlive(bool newAlive);
	void kill();

	std::string getName() const;
	void setName(std::string name);

	int getHealth() const;
	void setHealth(int health);
	void addHealth(int heal = 1);
	void takeHealth(int damage = 1);
	void healFull();

	int getMaxHealth() const;
	void setMaxHealth(int maxHealth);
	void addMaxHealth(int addMax = 1);
	void takeMaxHealth(int decreaseMax = 1);

	int getSave() const;
	void setSave(int save);
	void worsenSave();
	void improveSave();

	int getInSv() const;
	void setInSv(int invSv);
	void worsenInSv();
	void improveInSv();

	int getSaveAfterAp(int ap);

	int getToughness() const;
	void setToughness(int toughness);
	void worsenToughness(int debuff = 1);
	void improveToughness(int buff = 1);

	int getWeaponSkill() const;
	void setWeaponSkill(int weaponSkill);
	void worsenWeaponSkill();
	void imrpoveWeaponSkill();

	Weapon* getWeapon() const;
	void setWeapon(Weapon* weapon);
	void deleteWeapon();

	void buffUnit();

	void buffAllUnit();

	static Unit* unitFactory(int level);
};

class GuardsMan : public Unit
{
public:
	GuardsMan()
	{
		setName("Guardsman");
		setMaxHealth(1);
		setHealth(1);
		setSave(5);
		setInSv(7);
		setToughness(3);
		setWeaponSkill(4);
		setWeapon(new Lasgun);
	}
};

class SpaceMarine : public Unit
{
public:
	SpaceMarine()
	{
		setName("Space Marine");
		setMaxHealth(2);
		setHealth(2);
		setSave(3);
		setInSv(7);
		setToughness(5);
		setWeaponSkill(3);
		setWeapon(new Bolter);
	}
};

class Devastator : public Unit
{
public:
	Devastator()
	{
		setName("Devastator");
		setMaxHealth(2);
		setHealth(2);
		setSave(3);
		setInSv(7);
		setToughness(5);
		setWeaponSkill(4);
		setWeapon(new Lascannon);
	}
};

class Hellblaster : public Unit
{
public:
	Hellblaster()
	{
		setName("Hellblaster");
		setMaxHealth(2);
		setHealth(2);
		setSave(3);
		setInSv(7);
		setToughness(5);
		setWeaponSkill(3);
		setWeapon(new PlasmaGun);
	}
};

class Eliminator : public Unit
{
public:
	Eliminator()
	{
		setName("Eliminator");
		setMaxHealth(2);
		setHealth(2);
		setSave(3);
		setInSv(7);
		setToughness(4);
		setWeaponSkill(3);
		setWeapon(new BoltSniper);
	}
};

class Eradicator : public Unit
{
public:
	Eradicator()
	{
		setName("Eradicator");
		setMaxHealth(3);
		setHealth(3);
		setSave(3);
		setInSv(7);
		setToughness(6);
		setWeaponSkill(4);
		setWeapon(new HeavyBolter);
	}
};

class Terminator : public Unit
{
public:
	Terminator()
	{
		setName("Terminator");
		setMaxHealth(4);
		setHealth(4);
		setSave(2);
		setInSv(4);
		setToughness(6);
		setWeaponSkill(2);
		setWeapon(new PlasmaGun);
	}
};

//Use for custom enemies
class CustomUnit : public Unit
{
public:
	CustomUnit(std::string name = "Custom Unit",
		int health = 1,
		int maxHealth = 1,
		int save = 5,
		int insv = 7,
		int tough = 3,
		int skill = 4,
		//For the weapon
		std::string weaponName = "Custom Weapon",
		int shots = 1,
		int damage = 1,
		int ap = 0,
		int strength = 3,
		bool sustained = false,
		bool lethal = false,
		bool devastating = false)
	{
		setName(name);
		setMaxHealth(maxHealth);
		setHealth(health);
		setSave(save);
		setInSv(insv);
		setToughness(tough);
		setWeaponSkill(skill);
		setWeapon(new CustomWeapon(weaponName, shots, damage, ap, sustained, lethal, devastating));
	}
};







