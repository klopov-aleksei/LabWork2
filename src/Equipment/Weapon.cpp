#include "Weapon.h"
#include "Character/Character.h"

Weapon::Weapon(std::string_view name, int damage, int durability)
    : Equipment(name, Rarity::epic, durability)
    , baseDamage(damage) 
{
}

void Weapon::use(Character& user, std::unique_ptr<Item> self)
{
    std::unique_ptr<Weapon> weapon{ static_cast<Weapon*>(self.release()) };
    user.equipWeapon(std::move(weapon));
    std::cout << "Equipped " << m_name << " (" << m_currentDurability << "/" 
              << m_maxDurability << " durability)\n";
    user.takeActionPoints(1);

    runCustomEffect(user);
}

int Weapon::getBaseDamage() const 
{ 
    return baseDamage; 
}