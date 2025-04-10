#include "Armor.h"
#include "Character/Character.h"
#include "Random.h"
#include "Constants.h"

Armor::Armor(std::string_view name, int defense, int durability)
    : Equipment(name, Rarity::epic, durability)
    , baseDefense(defense) 
{
}

void Armor::use(Character& user, std::unique_ptr<Item> self)
{
    std::unique_ptr<Armor> armor{ static_cast<Armor*>(self.release()) };
    user.equipArmor(std::move(armor));
    std::cout << "Equipped " << m_name << " (" << m_currentDurability << "/" 
              << m_maxDurability << " durability)\n";
    user.takeActionPoints(1);

    runCustomEffect(user);
}

int Armor::getEffectiveDefense() const 
{
    return static_cast<int>(baseDefense * getCondition());
}

void Armor::takeDamage(int amount)
{
    amount = static_cast<int>(amount * static_cast<double>(
                Random::get(Constants::min_armor_reduce, Constants::max_armor_reduce)) / 100);
    Equipment::takeDamage(amount);
}
