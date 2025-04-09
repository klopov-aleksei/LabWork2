#include "Game.h"
#include "Character/MediumEnemy.h"

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

    auto enemy{ std::make_unique<MediumEnemy>() };
    startCombat(*enemy);
}

void Game::startCombat(NPC& enemy) 
{
    delete combatSystem;
    delete combatInterface;
    
    combatSystem = new CombatSystem{ *player, enemy };
    combatInterface = new CombatInterface{ *player, *combatSystem };
    combatSystem->startCombat(*combatInterface);
}