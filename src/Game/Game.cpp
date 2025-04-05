#include "Game.h"
#include "Character/NPC.h"

#include <iostream>

Game::~Game() 
{
    delete combatSystem;
    delete combatInterface;
}

void Game::start() 
{
    std::cout << "Welcome to the RPG!\n";

    player = characterCreation.createCharacter();
    player->displayStatus();

    NPC enemy("Orc", 50, 20, 3, 10); // Example enemy
    startCombat(enemy);
}

void Game::startCombat(NPC& enemy) 
{
    delete combatSystem;
    delete combatInterface;
    
    combatSystem = new CombatSystem{ *player, enemy };
    combatInterface = new CombatInterface{ *player, *combatSystem };
    combatSystem->startCombat(*combatInterface);
}