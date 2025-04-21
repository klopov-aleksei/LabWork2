#ifndef MELEE_ATTACK_H
#define MELEE_ATTACK_H

#include "TargetedSkill.h"

class MeleeAttack : public TargetedSkill 
{
public:
    MeleeAttack(int baseDamage = 0, int cost = Constants::melee_cost);
    
    void execute(Character& user, Character& target) override; 

    std::string_view getName() const override { return "Melee Attack"; }
};

#endif