#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Item.h"
#include <memory>

class Equipment : public Item 
{
protected:
    int m_maxDurability;
    int m_currentDurability;

public:
    Equipment(std::string_view name, Rarity rarity, int maxDurability);
    virtual void use(Character& user, std::unique_ptr<Item> self) = 0;
    virtual void takeDamage(int amount);
    void repair(int amount);
    bool isBroken() const;
    int getCurrentDurability() const;
    int getMaxDurability() const;
    double getCondition() const;
};

#endif