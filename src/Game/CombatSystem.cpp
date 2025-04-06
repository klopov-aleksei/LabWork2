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
    }
    
    std::cout << "\nCombat Over!\n";
    if (playerLost())
        std::cout << m_enemy->getName() << " wins!\n";
    else
        std::cout << m_player.getName() << " wins!\n";
}

void CombatSystem::handleTurn(CombatInterface& interface) 
{
    bool initialPlayerAdvantage = (m_player.getAgility() > m_enemy->getAgility());

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

    bool currentPlayerAdvantage = (m_player.getAgility() > m_enemy->getAgility());

    if (m_playerTurn)
    {
        // false && true = true = ok
        // true && false = false = ok
        // true && true = false = ok
        // false && false = false = ok
        if (!(initialPlayerAdvantage) && currentPlayerAdvantage)
        {
            std::cout << m_player.getName() << " is granted a free turn due to agility!\n";
            // free turn for the player).
        }
        else
        {
            m_playerTurn = false;
        }
    }
    else
    {
        // false && true = false = ok
        // true && false = true = ok
        // true && true = false = ok
        // false && false = false = ok
        if (initialPlayerAdvantage && !(currentPlayerAdvantage))
        {
            std::cout << m_enemy->getName() << " is granted a free turn due to agility change!\n";
            // m_playerTurn remains false (free turn for the enemy).
        }
        else
        {
            m_playerTurn = true;
        }
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