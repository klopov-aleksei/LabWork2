#ifndef COMBAT_INTERFACE_H
#define COMBAT_INTERFACE_H

#include "Character/PlayerCharacter.h"
#include "Character/NPC.h"
#include "CombatSystem.h"

class CombatInterface 
{
private:
    PlayerCharacter& m_player;
    CombatSystem& m_combatSystem;

public:
    CombatInterface(PlayerCharacter& player, CombatSystem& combatSystem);

    void displayCombatOptions();
    void processInput(int choice);

    void performAttack();
    void openInventory();
};

#endif