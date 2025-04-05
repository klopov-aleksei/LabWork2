#ifndef COMBAT_SYSTEM_H
#define COMBAT_SYSTEM_H

#include "Character/PlayerCharacter.h"
#include "Character/NPC.h"

class CombatInterface;

class CombatSystem 
{
private:
    PlayerCharacter& m_player;
    NPC* m_enemy;
    bool m_playerTurn{};

public:
    CombatSystem(PlayerCharacter& player, NPC& enemy);
    void startCombat(CombatInterface& interface);
    void handleTurn(CombatInterface& interface);

    Character& getEnemy() { return *m_enemy; }

    bool isCombatOver() const;
    bool playerLost() const;
};

#endif