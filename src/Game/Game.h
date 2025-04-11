#ifndef GAME_H
#define GAME_H

#include "CharacterCreation.h"
#include "CombatSystem.h"
#include "CombatInterface.h"

class PlayerCharacter;

class Game 
{
private:
    std::unique_ptr<PlayerCharacter> player{};
    std::unique_ptr<NPC> enemy{};
    CharacterCreation characterCreation;
    CombatSystem* combatSystem{};
    CombatInterface* combatInterface{};

public:
    Game() = default;
    ~Game();
    void start();
    void startCombat(NPC& enemy);
};

#endif