#include "Block.h"
#include "Character/PlayerCharacter.h"
#include "Character/Warrior.h"

#include <iostream>

void Block::execute(Character& user)
{
    int cost{ getCost() };
    auto* pc = dynamic_cast<PlayerCharacter*>(&user);
    if (pc != nullptr) 
    { 
        if (pc->hasEasyBlock()) 
            cost = (cost > 1) ? cost - 2 : cost;
    }
    user.setBlocking(true);
    user.takeActionPoints(cost);
    if (pc != nullptr)
        std::cout << user.getName() << " blocks!\n";
}