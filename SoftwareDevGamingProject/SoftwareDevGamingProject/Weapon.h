#pragma once

#include <iostream>

class Weapon
{
private:
	std::string name = "Default";
	int shots = 1;
	int damage = 1;
	int ap = 0;
	int strength = 3;
	bool sustained = false;
	bool lethal = false;
	bool devastating = false;

public:
	Weapon(std::string name = "Lasgun", int shots = 1, int damage = 1, int ap = 0, int strength = 3, bool sustained = false, bool lethal = false, bool devastating = false);
	~Weapon();

	void printDetails();
	void setName(std::string name);
	std::string getName() const;

	void setShots(int shots);
	int getShots() const;
	void addShots(int buff = 1);


	void setDamage(int damage);
	int getDamage() const;
	void addDamage(int buff = 1);

	void setAp(int ap);
	int getAp() const;
	void addAp(int buff = 1);

	void setStrength(int strength);
	int getStrength() const;
	void addStrength(int buff = 1);

	void setSustained(bool sustained);
	bool isSustained() const;
	void toggleSustained();

	void setLethal(bool lethal);
	bool isLethal() const;
	void toggleLethal();

	void setDevastating(bool devastating);
	bool isDevastating() const;
	void toggleDevastating();

	void buffAll();
};

class Bolter : public Weapon
{
public:
	Bolter()
	{
		setName("Bolter");
		setShots(2);
		setDamage(1);
		setAp(1);
		setStrength(5);
	}
};

class Lasgun : public Weapon
{
public:
	Lasgun()
	{
		setName("Lasgun");
		setShots(1);
		setDamage(1);
		setAp(0);
		setStrength(3);
	}
};

class HeavyBolter : public Weapon
{
public:
	HeavyBolter()
	{
		setName("Heavy Bolter");
		setShots(3);
		setDamage(2);
		setAp(1);
		setStrength(5);
		setSustained(true);
	}
};

class BoltSniper : public Weapon
{
public:
	BoltSniper()
	{
		setName("Bolt Sniper");
		setShots(1);
		setDamage(4);
		setAp(2);
		setStrength(5);
		setDevastating(true);
	}
};

class Lascannon : public Weapon
{
public:
	Lascannon()
	{
		setName("Lascannon");
		setShots(1);
		setDamage(7);
		setAp(3);
		setStrength(12);
	}
};

class PlasmaGun : public Weapon
{
public:
	PlasmaGun()
	{
		setName("Plasma Gun");
		setShots(2);
		setDamage(2);
		setAp(4);
		setStrength(8);
		setLethal(true);
	}
};

class CustomWeapon : public Weapon
{
public:
	CustomWeapon(std::string name = "Custom Weapon",
		int shots = 1,
		int damage = 1,
		int ap = 0,
		int strength = 3,
		bool sustained = false,
		bool lethal = false,
		bool devastating = false)
	{
		setName(name);
		setShots(shots);
		setDamage(damage);
		setAp(ap);
		setStrength(strength);
		setSustained(sustained);
		setLethal(lethal);
		setDevastating(devastating);
	}
};
