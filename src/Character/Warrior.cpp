#include "Character/Warrior.h"

Warrior::Warrior(std::string_view name)
    : PlayerCharacter(name, 5, 10)
    , m_blockSuccess{ false }
    , m_damageBuff{ false }
{ 
}

void Warrior::setBlockSuccess(bool success) 
{
    m_blockSuccess = success;
}

void Warrior::resetActionPoints() 
{
    PlayerCharacter::resetActionPoints();
    if (m_blockSuccess) 
    {
        m_damageBuff = true;
        m_blockSuccess = false;
        std::cout << getName() << " gains 20%" << " damage bonus for the next attack!\n";
    }
}

bool Warrior::isDamageBuffActive() const 
{
    return m_damageBuff;
}

void Warrior::resetDamageBuff() 
{
    m_damageBuff = false;
}