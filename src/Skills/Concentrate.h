#ifndef CONCENTRATION_H
#define CONCENTRATION_H

#include "UntargetedSkill.h"

class Concentrate : public UntargetedSkill 
{
public:
    Concentrate() : UntargetedSkill(Skill::Type::Utility, Constants::conc_cost) { }
    void execute(Character& user) override;

    std::string_view getName() const override { return "Concentrate"; } 
};

#endif