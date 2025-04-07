#include "Block.h"
#include "Character/PlayerCharacter.h"

#include <iostream>

void Block::execute(Character& user)
{
    int cost{ getCost() };
    if (auto* pc = dynamic_cast<PlayerCharacter*>(&user)) 
    { 
        if (pc->hasEasyBlock()) cost = (cost > 1) ? cost - 2 : cost;
    } 
    user.setBlocking(true);
    user.takeActionPoints(cost);
    std::cout << user.getName() << " blocks!\n";
}