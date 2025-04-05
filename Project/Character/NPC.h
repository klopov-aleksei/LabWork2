#ifndef NPC_H
#define NPC_H

#include "Character/Character.h"
#include <string_view>
#include <iostream>

class NPC : public Character 
{
public:
    NPC(std::string_view name, int strength, int intelligence, int agility, int mana)
        : Character(name, strength, intelligence, agility, mana) {}

    virtual ~NPC() = default;
    void displayStatus() const override 
    {
        std::cout << "[Enemy] " << getName() 
                  << " | Health: " << getHealth() << "\n";
    }
};

#endif