#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include "Equipment.h"

#include <memory>

class Weapon : public Equipment 
{
private:
    int baseDamage;

public:
    Weapon(std::string_view name, int damage, int durability);
    void use(Character& user, std::unique_ptr<Item> self) override;
    int getBaseDamage() const;
};

#endif