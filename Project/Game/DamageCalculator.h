#ifndef DAMAGE_CALCULATOR_H
#define DAMAGE_CALCULATOR_H

#include "Character/Character.h"

class DamageCalculator
{
private:
    int m_attackCount{};
    int m_finalDamage{};
    int m_armorDamage{};

public:
    DamageCalculator() = default;
    
    void incrementAttackCount() { ++m_attackCount; }
    void resetAttackCount() { m_attackCount = 0; }

    friend void calculateDamage(DamageCalculator& dmgCalc, 
        Character& target, int baseDamage, int statBonus);

    friend void Character::takeDamage(DamageCalculator& dmgCalc);
};

#endif
