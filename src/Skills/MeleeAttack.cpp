#include "MeleeAttack.h"
#include "Character/Character.h"
#include "Character/PlayerCharacter.h"
#include "Character/Warrior.h"
#include "Equipment/Weapon.h"
#include "Game/computeStatBonus.h"
#include "Game/DamageCalculator.h"
#include "Random.h"
#include "Constants.h"

#include <iostream>

MeleeAttack::MeleeAttack(int baseDamage, int cost) 
	: TargetedSkill(Skill::Type::Damage, cost, baseDamage)
{
}

void MeleeAttack::execute(Character& user, Character& target) 
{
    int cost{ getCost() };
    auto* weapon = user.getWeapon();
    if (weapon)
    {
        std::string name = weapon->getName();
        if (name == "Excalibur")
        {
            cost -= 1;
        }
        else if (name == "Aegis Blade")
        {
            if (dynamic_cast<Warrior*>(&user))
                cost -= 2;
        }
    }
    int finalCost = std::max(cost, 1);

    if (user.getActionPoints() < finalCost)
    {
        std::cout << "Not enough action points to execute " << getName() << ".\n";
        return;
    }

    user.incrementAttackCount();
    int attackCount = user.getAttackCount();
    DamageCalculator dmgCalc;

    std::cout << user.getName() << " attacks " << target.getName() << "!\n";
    int baseDamage{ Random::get(Constants::min_attack_bonus, Constants::max_attack_bonus) };
    if (!weapon)
    {
        std::cout << user.getName() << " has not got any weapon.\n";
        calculateDamage(dmgCalc, target, baseDamage, computeStatBonus(user, baseDamage, true), attackCount);
        target.takeDamage(dmgCalc);
        user.takeActionPoints(finalCost);
        return;
    }
    baseDamage = weapon->getBaseDamage();

    Warrior* warrior = dynamic_cast<Warrior*>(&user);
    if (warrior && warrior->isDamageBuffActive()) 
    {
        baseDamage = static_cast<int>(baseDamage * 1.2);
        warrior->resetDamageBuff();
        std::cout << user.getName() << " strikes with 20%" << " increased damage from a successful block!\n";
    }

    int statBonus{ computeStatBonus(user, baseDamage, true) }; // true = for melee using strength
    calculateDamage(dmgCalc, target, baseDamage, statBonus, attackCount);
    target.takeDamage(dmgCalc);
    user.takeActionPoints(finalCost);
    if (weapon)
    {
        int durabilityLoss{ Random::get(Constants::min_weapon_decoy, Constants::max_weapon_decoy) };
        weapon->takeDamage(durabilityLoss);
        if (weapon->isBroken()) 
        {
            std::cout << user.getName() << "'s " << weapon->getName() << " broke!\n";
            user.equipWeapon(nullptr);
        }
    }
}