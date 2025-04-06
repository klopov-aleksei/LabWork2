#ifndef HEAL_H
#define HEAL_H

#include "Constants.h"

class Heal : public UntargetedSkill 
{
public:
    Heal() : UntargetedSkill(Skill::Type::Heal, Constants::heal_cost) { }
    void execute(Character& user) override 
    {
        user.increaseHealth(Constants::healAmount);
        user.takeActionPoints(getCost());
        std::cout << user.getName() << " heals for " << Constants::healAmount << " HP.\n";
    }

    std::string_view getName() const override { return "Heal"; }
};

#endif