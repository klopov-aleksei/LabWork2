#include "SpellCast.h"
#include "Character/PlayerCharacter.h"
#include "Character/Mage.h"
#include "Game/computeStatBonus.h"
#include "Game/DamageCalculator.h"
#include "Random.h"
#include "Constants.h"

#include <iostream>

SpellCast::SpellCast(int manaCost, int damage, int cost)
    : TargetedSkill(Skill::Type::Damage, cost, damage)
    , m_manaCost{ manaCost }
{
}

void SpellCast::execute(Character& user, Character& target) 
{
    int cost{ getCost() };
    if (user.getActionPoints() < cost)
    {
        std::cout << "Not enough action points to execute " << getName() << ".\n";
        return;
    }

    int bonusDamage{ 0 };
    int manaCost{ m_manaCost };
    if (auto* weapon = user.getWeapon())
    {
        std::string name = weapon->getName();
        if (name == "Staff")
        {
            bonusDamage += 10;
            if (dynamic_cast<Mage*>(&user))
                manaCost -= 5;
        }
        else if (name == "Aegis Blade")
        {
            bonusDamage += 20;
            if (dynamic_cast<Mage*>(&user))
                manaCost -= 5;
        }
    }

    if (user.getMana() < manaCost) 
    {
        std::cout << user.getName() << " tries to cast a spell but doesn't have enough mana!\n";
        return;
    }

    user.incrementAttackCount();
    std::cout << user.getName() << " casts a spell on " << target.getName() << '\n';
    int attackCount = user.getAttackCount();

    int baseDamage{ getDamage() + bonusDamage };
    int statBonus{ computeStatBonus(user, baseDamage, false) };

    DamageCalculator dmgCalc;
    dmgCalc.markAsSpell();
    calculateDamage(dmgCalc, target, baseDamage, statBonus, attackCount);
    target.takeDamage(dmgCalc);
    user.takeActionPoints(cost);
    user.useMana(manaCost);
}

