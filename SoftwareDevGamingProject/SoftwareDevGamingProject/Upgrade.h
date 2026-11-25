#pragma once
#include "Weapon.h"
#include "Unit.h"
#include <iostream>

class Upgrade
{
public:
	virtual void useUpgrade(Unit& unit) const = 0;
	virtual std::string getName() const = 0;

	static Upgrade* upgradeFactory(const std::string& upgrade);
	static Upgrade* randomUpgradeFactory();
};

class GunBuff : public Upgrade
{
public:
	std::string getName() const override;

	void useUpgrade(Unit& unit) const override;
};

class UnitBuff : public Upgrade
{
public:
	std::string getName() const override;

	void useUpgrade(Unit& unit) const override;
};

class HealthBuff : public Upgrade
{
public:
	std::string getName() const override;

	void useUpgrade(Unit& unit) const override;
};

class ShotBuff : public Upgrade
{
public: 
	std::string getName() const override;

	void useUpgrade(Unit& unit) const override;
};

class Heal : public Upgrade
{
public:
	std::string getName() const override;

	void useUpgrade(Unit& unit) const override;
};

