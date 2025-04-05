#include "Block.h"

#include <iostream>

void Block::execute(Character& user)
{
    user.setBlocking(true);
    user.takeActionPoints(getCost());
    std::cout << user.getName() << " blocks!\n";
}