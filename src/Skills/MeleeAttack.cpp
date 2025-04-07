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


MeleeAttack::MeleeAttack(int baseDamage) 
	: TargetedSkill(Skill::Type::Damage, Constants::melee_cost, baseDamage)
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
    if (!user.getWeapon())
    {
        std::cout << "\nYou have not got any weapon.\n";
        target.takeDamage(Random::get(Constants::min_attack_bonus, Constants::max_attack_bonus));
        return;
    }

    int baseDamage{ user.getWeapon()->getBaseDamage() };
    int statBonus{ computeStatBonus(user, baseDamage, true) }; // true = for melee using strength

    DamageCalculator dmgCalc; // change: resets every time
    dmgCalc.incrementAttackCount();
    calculateDamage(dmgCalc, target, baseDamage, statBonus);
    
    target.takeDamage(dmgCalc);
    user.takeActionPoints(finalCost);

    if (user.getWeapon()->isBroken()) 
    {
        std::cout << "Your " << user.getWeapon()->getName() << " broke!\n";
        user.equipWeapon(nullptr);
    }
}