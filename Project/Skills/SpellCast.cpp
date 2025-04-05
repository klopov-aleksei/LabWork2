#include "SpellCast.h"
#include "Random.h"
#include "Constants.h"
#include "Game/computeStatBonus.h"
#include "Game/DamageCalculator.h"

#include <iostream>

SpellCast::SpellCast(int manaCost, int damage)
    : TargetedSkill(Skill::Type::Damage, 3, damage)
    , m_manaCost(manaCost)
{
}

void SpellCast::execute(Character& user, Character& target) 
{
    if (user.getMana() < m_manaCost) 
    {
        std::cout << user.getName() << " tries to cast a spell but doesn't have enough mana!\n";
        return;
    }

    int baseDamage{ getDamage() };
    int statBonus{ computeStatBonus(user, baseDamage, false) }; // false = using intelligence

    DamageCalculator dmgCalc;
    dmgCalc.incrementAttackCount();
    calculateDamage(dmgCalc, target, baseDamage, statBonus);

    std::cout << user.getName() << " casts a spell on " << target.getName() << '\n';

    user.takeDamage(dmgCalc);
    user.takeActionPoints(getCost());
    user.useMana(m_manaCost);
}

