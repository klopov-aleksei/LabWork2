#ifndef STAT_MODIFIER_H
#define STAT_MODIFIER_H

enum class Target
{
    self,
    enemy,
    armor,
    weapon
};

enum class Stat
{
    none,           // jewellery, equipment
    health,         // food, heal
    mana,           // mana_potion
    maxHealth,      // heal
    maxMana,        // potion
    strength,       // potion
    intelligence,   // potion
    agility,        // potion
    actionPoints,   // potion
    repair,         // repair kit, tools
    damage,         // scrolls, spells
};

struct StatModifier
{
    Stat stat{};
    int value{};
    Target target{ Target::self };
};

#endif