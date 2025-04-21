#ifndef DAMAGE_CALCULATOR_H
#define DAMAGE_CALCULATOR_H

#include "Character/Character.h"

class DamageCalculator
{
private:
    int m_finalDamage{ 0 };
    int m_armorDamage{ 0 };
    bool m_isSpell{ false };

public:
    DamageCalculator() = default;
    void markAsSpell() { m_isSpell = true; }
    bool isSpell() const { return m_isSpell; }

    friend void calculateDamage(DamageCalculator& dmgCalc, 
        Character& target, int baseDamage, int statBonus, int attackCount);

    friend void Character::takeDamage(DamageCalculator& dmgCalc);
};

#endif