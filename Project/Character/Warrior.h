#ifndef WARRIOR_H
#define WARRIOR_H

#include "PlayerCharacter.h"
#include "Skills/MeleeAttack.h"
#include "Skills/Block.h"

class Warrior : public PlayerCharacter 
{
public:
    Warrior(std::string_view name)
        : PlayerCharacter(name, 5, 10) { }
};
#endif