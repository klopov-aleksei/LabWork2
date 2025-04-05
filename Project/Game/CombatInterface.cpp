#include "CombatInterface.h"
#include "Equipment/Inventory.h"
#include "Skills/Block.h"
#include "Skills/Heal.h"
#include "Skills/Investigate.h"
#include "Skills/Concentrate.h"
#include "Skills/MeleeAttack.h"
#include "Skills/SpellCast.h"

#include <iostream>
#include <limits>

CombatInterface::CombatInterface(PlayerCharacter& player, CombatSystem& combatSystem) 
    : m_player{ player }
    , m_combatSystem{ combatSystem }
{ 
}

void CombatInterface::displayCombatOptions() 
{
    while (m_player.getActionPoints() > 0) 
    {
        std::cout << "\n--- Combat Options ---\n";
        std::cout << "1) Attack\n2) Block\n3) Inventory\n4) Investigate\n5) Concentrate\n";
        if (m_player.hasHealing())
            std::cout << "6) Heal\n";
        std::cout << "0) END TURN\n";
        int choice;
        std::cin >> choice;
        processInput(choice);
    }
}

void CombatInterface::processInput(int choice) 
{
    switch(choice) 
    {
    case 0:     m_player.setActionPoints(0); break;
    case 1:     performAttack(); break;
    case 2:     Block().execute(m_player); m_player.setActionPoints(0); break;
    case 3:     openInventory(); break;
    case 4:     Investigate().execute(m_player); break;
    case 5:     Concentrate().execute(m_player); break;
    case 6:     if (m_player.hasHealing()) Heal().execute(m_player); else std::cout << "Invalid option.\n"; break;
    default:    std::cout << "Invalid input.\n";
    }
};

void CombatInterface::performAttack()
{
    if (m_player.canUseSpell())
    {
        std::cout << "Choose Attack Type:\n1) Melee  2) Spell\n";
        int atkType;
        std::cin >> atkType;
        while (!(std::cin) || atkType < 1 || atkType > 2)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Choose a valid attack type: ";
        }
        if (atkType == 1) 
        {
            MeleeAttack().execute(m_player, m_combatSystem.getEnemy());
        } 
        else if (atkType == 2) 
        {
            SpellCast().execute(m_player, m_combatSystem.getEnemy());
        }
    }
    else
    {   
        MeleeAttack().execute(m_player, m_combatSystem.getEnemy());
    }
}

void CombatInterface::openInventory() 
{
    m_player.getInventory().display();
    std::cout << "Enter item number to use (positive number), negative number to dispose, or 0 to exit: ";
    int itemChoice;
    while (true)
    {
        std::cin >> itemChoice;
        if (std::cin.fail() || std::abs(itemChoice) > m_player.getInventory().size())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid index. Try again.\n";
            continue;
        }
        else if (itemChoice < 0 && (-itemChoice) <= m_player.getInventory().size()) {
            m_player.getInventory().removeItem(itemChoice);
        } 
        else if (itemChoice == 0) 
        {
            break;
        }
        m_player.getInventory().useItem(itemChoice, m_player, &(m_combatSystem.getEnemy()));
        displayCombatOptions();
        break;
    }
}