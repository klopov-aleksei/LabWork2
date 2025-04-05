#include "CombatSystem.h"
#include "CombatInterface.h"

#include <iostream>

CombatSystem::CombatSystem(PlayerCharacter& player, NPC& enemy)
    : m_player{ player }
    , m_enemy{ &enemy }
{
    m_playerTurn = (m_player.getAgility() >= (m_enemy->getAgility()));
}

void CombatSystem::startCombat(CombatInterface& interface) 
{
    while (!isCombatOver()) 
    {
        handleTurn(interface);
        m_playerTurn = !m_playerTurn;
    }
    
    std::cout << "\nCombat Over!\n";
    if (playerLost())
        std::cout << m_enemy->getName() << " wins!\n";
    else
        std::cout << m_player.getName() << " wins!\n";
}

void CombatSystem::handleTurn(CombatInterface& interface) 
{
    if (m_playerTurn) 
    {
        m_player.resetActionPoints();
        interface.displayCombatOptions();
    } 
    else 
    {
        m_enemy->resetActionPoints();
        // Enemy AI logic
    }
}

bool CombatSystem::isCombatOver() const 
{
    return playerLost() || (m_enemy->getHealth()) <= 0;
}

bool CombatSystem::playerLost() const
{
    return m_player.getHealth() <= 0;
}