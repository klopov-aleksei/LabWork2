#include "Equipment.h"
#include <algorithm>

Equipment::Equipment(std::string_view name, Rarity rarity, int durability) 
    : Item(name, rarity)
    , m_maxDurability(durability)
    , m_currentDurability(durability) 
{
}

void Equipment::takeDamage(int amount) 
{
    m_currentDurability = std::max(0, m_currentDurability - amount);
}

void Equipment::repair(int amount) 
{
    m_currentDurability = std::clamp(m_currentDurability + amount, 0, m_maxDurability);
}

bool Equipment::isBroken() const 
{
    return m_currentDurability <= 0;
}

int Equipment::getCurrentDurability() const 
{ 
    return m_currentDurability; 
}

int Equipment::getMaxDurability() const 
{ 
    return m_maxDurability; 
}

double Equipment::getCondition() const 
{ 
    return static_cast<double>(m_currentDurability) / m_maxDurability; 
}