#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"

#include <memory>
#include <algorithm>
#include <iostream>
#include <string_view>

class Character;

class Armor : public Item 
{
private:
    int baseDefense;
    int maxDurability;
    int currentDurability;
    
public:
    Armor(std::string_view name, int defense, int durability);

    void use(Character& user, std::unique_ptr<Item> self);

    int getEffectiveDefense() const;

    void takeDamage(int amount);

    void repair(int amount);

    bool isBroken() const { return currentDurability <= 0; }
    int getCurrentDurability() const { return currentDurability; }
    int getMaxDurability() const { return maxDurability; }
    double getCondition() const { return static_cast<double>(currentDurability) / maxDurability; }
};

#endif