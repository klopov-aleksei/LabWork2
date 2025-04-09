#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <memory>
#include <iostream>

#include "Item.h"

class Weapon : public Item 
{
protected:
    int baseDamage;
    int maxDurability;
    int currentDurability;

public:
    Weapon(std::string_view name, int damage, int durability);

    ~Weapon() override = default;

    void repair(int amount);

    void use(Character& user, std::unique_ptr<Item> self);

    bool isBroken() const { return currentDurability <= 0; }
    int getBaseDamage() const { return baseDamage; }
    int getCurrentDurability() const { return currentDurability; }
    int getMaxDurability() const { return maxDurability; }
    double getCondition() const { return static_cast<double>(currentDurability) / maxDurability; }
};

#endif