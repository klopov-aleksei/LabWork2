#include "Armor.h"
#include "Character/Character.h"
#include "Random.h"
#include "Constants.h"

Armor::Armor(std::string_view name, int defense, int durability) 
	: Item(name, Rarity::epic)
    , baseDefense{ defense }
    , maxDurability{ durability }
    , currentDurability{ durability } 
{
}

void Armor::use(Character& user, std::unique_ptr<Item> self)
{
    std::unique_ptr<Armor> armor{ static_cast<Armor*>(self.release()) };
    user.equipArmor(std::move(armor));
    std::cout << "Equipped " << m_name << " (" << currentDurability << "/" 
              << maxDurability << " durability)\n";
    user.takeActionPoints(1);

    runCustomEffect(user);
}

int Armor::getEffectiveDefense() const 
{
    return static_cast<int>(baseDefense * (currentDurability / static_cast<double>(maxDurability)));
}

void Armor::takeDamage(int amount)
{
    amount = static_cast<int>(amount * static_cast<double>(
                Random::get(Constants::min_armor_reduce, Constants::max_armor_reduce)) / 100);
    currentDurability = std::max(0, currentDurability - amount);
}

void Armor::repair(int amount)
{
    currentDurability = std::clamp(currentDurability + amount, 0, maxDurability);
}