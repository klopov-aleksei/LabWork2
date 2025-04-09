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
    if (auto* weapon = user.getWeapon())
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

    if (!user.getWeapon())
    {
        std::cout << "\nYou have not got any weapon.\n";
        int baseDamage{ Random::get(Constants::min_attack_bonus, Constants::max_attack_bonus) };
        calculateDamage(dmgCalc, target, baseDamage, computeStatBonus(user, baseDamage, true), attackCount);
        target.takeDamage(dmgCalc);
        user.takeActionPoints(finalCost);
        return;
    }

    Weapon* weapon = user.getWeapon();
    int baseDamage = weapon->getBaseDamage();
    int statBonus{ computeStatBonus(user, baseDamage, true) }; // true = for melee using strength
    calculateDamage(dmgCalc, target, baseDamage, statBonus, attackCount);
    target.takeDamage(dmgCalc);
    user.takeActionPoints(finalCost);

    int durabilityLoss{ Random::get(Constants::min_weapon_decoy, Constants::max_weapon_decoy) };
    weapon->repair(durabilityLoss);
    std::cout << weapon->getName() << " durability: " 
              << weapon->getCurrentDurability() << "/"
              << weapon->getMaxDurability() << "\n";
    if (weapon->isBroken()) 
    {
        std::cout << user.getName() << "'s " << user.getWeapon()->getName() << " broke!\n";
        user.equipWeapon(nullptr);
    }
}