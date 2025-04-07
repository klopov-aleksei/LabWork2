#include "Heal.h"
#include <iostream>

void Heal::execute(Character& user)
{
    int cost{ getCost() };
    if (user.getActionPoints() < cost) 
    {
        std::cout << "Not enough action points to execute " << getName() << ".\n";
        return;
    }
    user.increaseHealth(Constants::healAmount);
    user.takeActionPoints(cost);
    std::cout << user.getName() << " heals for " << Constants::healAmount << " HP.\n";
}
