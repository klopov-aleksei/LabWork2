#include "Heal.h"
#include <iostream>

Heal::Heal(int cost, int healAmount) 
    : UntargetedSkill(Skill::Type::Heal, cost)
    , m_healAmount{ healAmount }
{ 
}

void Heal::execute(Character& user)
{
    int cost{ getCost() };
    if (user.getActionPoints() < cost) 
    {
        std::cout << "Not enough action points to execute " << getName() << ".\n";
        return;
    }
    std::cout << user.getName() << " heals for " << getHealAmount() << " HP.\n";
    user.increaseHealth(Constants::healAmount);
    user.takeActionPoints(cost);
}
