#include "Game.h"
#include "Character/EasyEnemy.h"
#include "Character/MediumEnemy.h"
#include "Character/HardEnemy.h"

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

    int difficulty;
    do 
    {
        std::cout << "Choose difficulty:\n1. Easy\n2. Medium\n3. Hard\n";
        std::cin >> difficulty;
    } while (difficulty < 1 || difficulty > 3);
    
    switch (difficulty)
    {
        case 1:
            enemy = std::make_unique<EasyEnemy>();
            break;
        case 2:
            enemy = std::make_unique<MediumEnemy>();
            break;
        case 3:
            enemy = std::make_unique<HardEnemy>();
            break;
    }
    
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