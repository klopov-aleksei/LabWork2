#include "Weapon.h"
#include "Character/Character.h"
#include "Random.h"
#include "Constants.h"

#include <algorithm>

Weapon::Weapon(std::string_view name, int damage, int durability)
    : Item(name, Rarity::epic)
    , baseDamage(damage)
    , maxDurability(durability)
    , currentDurability(durability) 
{
}

void Weapon::repair(int amount) 
{
    currentDurability = std::clamp(currentDurability + amount, 0, maxDurability);
}

void Weapon::use(Character& user, std::unique_ptr<Item> self)
{
    std::unique_ptr<Weapon> weapon{ static_cast<Weapon*>(self.release()) };
    user.equipWeapon(std::move(weapon));
    std::cout << "Equipped " << m_name << " (" << currentDurability << "/" 
              << maxDurability << " durability)\n";
}