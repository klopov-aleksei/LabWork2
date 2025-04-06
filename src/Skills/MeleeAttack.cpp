#include "MeleeAttack.h"
#include "Character/Character.h"
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
    if (!user.getWeapon())
    {
        std::cout << "\nYou have not got any weapon.\n";
        return;
    }

    int baseDamage{ user.getWeapon()->getBaseDamage() };
    int statBonus{ computeStatBonus(user, baseDamage, true) }; // true = for melee using strength

    DamageCalculator dmgCalc; // change: resets every time
    dmgCalc.incrementAttackCount();
    calculateDamage(dmgCalc, target, baseDamage, statBonus);
    
    target.takeDamage(dmgCalc);
    user.takeActionPoints(getCost());

    if (user.getWeapon()->isBroken()) 
    {
        std::cout << "Your " << user.getWeapon()->getName() << " broke!\n";
        user.equipWeapon(nullptr);
    }
}