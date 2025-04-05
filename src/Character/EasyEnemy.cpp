#include "Character/EasyGoblin.h"

EasyGoblin::EasyGoblin() 
    : NPC("Goblin Grunt", 80, 8)
{
    skills.emplace_back(std::make_unique<MeleeAttack>());
}