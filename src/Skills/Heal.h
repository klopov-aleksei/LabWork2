#ifndef HEAL_H
#define HEAL_H

#include "Constants.h"
#include "UntargetedSkill.h"
#include <string_view>

class Heal : public UntargetedSkill 
{
private:
    int m_healAmount{};

public:
    Heal(int cost = Constants::heal_cost, int healAmount = Constants::healAmount);
    
    void execute(Character& user) override;

    int getHealAmount() const { return m_healAmount; }
    std::string_view getName() const override { return "Heal"; }
};

#endif