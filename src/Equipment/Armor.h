#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"
#include "Equipment.h"

#include <memory>

class Armor : public Equipment {
    int baseDefense;

public:
    Armor(std::string_view name, int defense, int durability);
    void use(Character& user, std::unique_ptr<Item> self) override;
    int getEffectiveDefense() const;
    void takeDamage(int amount) override;
};

#endif