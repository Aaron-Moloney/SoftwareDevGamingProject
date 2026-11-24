#include "Weapon.h"
#include <iostream>

Weapon::Weapon(std::string name, int shots, int damage, int ap, int strength, bool sustained, bool lethal, bool devastating)
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
Weapon::~Weapon()
{
	std::cout << "Deleting " << getName() << "\n";
}

void Weapon::printDetails()
{
	std::cout << "Name: " << name << " | Shots: " << shots << " | Damage: " << damage << " | Ap: " << ap
		<< " | Strength: " << strength << " | Sus: " << sustained << " | Lethal: " << lethal << " | Dev: " << devastating << "\n";
}

//void use(Unit* target);


//Getters and setters, checks for invalid values, defaults to minimum allowed if invalid.
//Only ever buff weapons
void Weapon::setName(std::string name) { name.length() > 0 ? this->name = name : this->name = "Weapon"; }
std::string Weapon::getName() const { return name; }

void Weapon::setShots(int newShots) { newShots > 0 ? shots = newShots : shots = 1; }
int Weapon::getShots() const { return shots; }
void Weapon::addShots(int buff) { buff > 0 ? setShots(getShots() + buff) : setShots(getShots()); }


void Weapon::setDamage(int newDamage) { newDamage > 0 ? damage = newDamage : damage = 1; }
int Weapon::getDamage() const { return damage; }
void Weapon::addDamage(int buff) { buff > 0 ? setDamage(getDamage() + buff) : setDamage(getDamage()); }

void Weapon::setAp(int newAp) { newAp >= 0 ? ap = newAp : ap = 0; }
int Weapon::getAp() const { return ap; }
void Weapon::addAp(int buff) { buff > 0 ? setAp(getAp() + buff) : setAp(getAp()); }

void Weapon::setStrength(int newStrength) { newStrength > 0 ? strength = newStrength : strength = 1; }
int Weapon::getStrength() const { return strength; }
void Weapon::addStrength(int buff) { buff > 0 ? setStrength(getStrength() + buff) : setStrength(getStrength()); }

void Weapon::setSustained(bool newSustained) { sustained = newSustained; }
bool Weapon::isSustained() const { return sustained; }
//Toggle method for bool values if needed.
void Weapon::toggleSustained() { sustained = !sustained; }

void Weapon::setLethal(bool newLethal) { lethal = newLethal; }
bool Weapon::isLethal() const { return lethal; }
void Weapon::toggleLethal() { lethal = !lethal; }

void Weapon::setDevastating(bool newDevastating) { devastating = newDevastating; }
bool Weapon::isDevastating() const { return devastating; }
void Weapon::toggleDevastating() { devastating = !devastating; }

void Weapon::buffAll()
{
	addShots();
	addDamage();
	addAp();
	addStrength();
}
