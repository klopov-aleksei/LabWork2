#pragma once

#include "PlayerCharacter.h"
#include "Skills/SpellCast.h"
#include "Skills/MeleeAttack.h"
#include "Skills/Block.h"

class Mage : public PlayerCharacter {
public:
    Mage(std::string_view name) 
        : PlayerCharacter(name, 7, 50) { }
};