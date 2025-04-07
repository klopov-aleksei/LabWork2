#ifndef HEAL_H
#define HEAL_H

#include "Constants.h"
#include "UntargetedSkill.h"
#include <string_view>

class Heal : public UntargetedSkill 
{
public:
    Heal() : UntargetedSkill(Skill::Type::Heal, Constants::heal_cost) { }
    void execute(Character& user) override;

    std::string_view getName() const override { return "Heal"; }
};

#endif