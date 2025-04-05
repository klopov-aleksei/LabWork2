#ifndef CONCENTRATION_H
#define CONCENTRATION_H

#include "UntargetedSkill.h"

class Concentrate : public UntargetedSkill 
{
public:
    Concentrate() : UntargetedSkill(Skill::Type::Utility, 3) { }
    void execute(Character& user) override 
    {
        user.increaseMana(Constants::concentrationManaRestore);
        user.increaseActionPoints(1);
        user.takeActionPoints(getCost());
        std::cout << user.getName() << " concentrates, restoring mana and boosting next turn's AP.\n";
    }

    std::string_view getName() const override { return "Concentrate"; } 
};

#endif