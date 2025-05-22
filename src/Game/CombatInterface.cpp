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
#include <sstream>

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
        std::cout << "6) Display Status\n";
        if (m_player.hasHealing())
            std::cout << "7) Heal\n";
        std::cout << "0) END TURN\n";

        int choice;
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            continue;
        }
        processInput(choice);
    }
}

void CombatInterface::processInput(int choice) 
{
    switch(choice) 
    {
    case 0:     m_player.takeActionPoints(m_player.getActionPoints()); break;
    case 1:     performAttack(); break;
    case 2:     Block().execute(m_player); break;
    case 3:     openInventory(); break;
    case 4:     if (m_player.getInventory().isFull()) std::cout << "Inventory is full!"; else Investigate().execute(m_player); break;
    case 5:     Concentrate().execute(m_player); break;
    case 6:     m_player.displayStatus(); break;
    case 7:     if (m_player.hasHealing()) Heal().execute(m_player); else std::cout << "Invalid option.\n"; break;
    default:    std::cout << "Invalid input.\n";
    }
};

void CombatInterface::performAttack()
{
    if (m_player.canUseSpell())
    {
        int atkType = -1;
        bool validInput = false;

        while (!validInput) 
        {
            std::cout << "Choose Attack Type:\n"
                      << "1) Melee\n2) Spell\n0) Cancel\n";
            
            if (!(std::cin >> atkType)) 
            {
                // Handle non-integer input
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter 0, 1, or 2.\n";
                continue;
            }
            
            if (atkType == 0) 
            {
                // Player chose to cancel
                std::cout << "Attack cancelled.\n";
                return;
            }
            
            if (atkType == 1 || atkType == 2) 
            {
                validInput = true;
            } 
            else 
            {
                std::cout << "Invalid choice! Please enter 0, 1, or 2.\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
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
    if (!(m_player.getInventory().isEmpty()))
    {
        std::cout << "Enter item number to use (positive number), negative number to dispose, or 0 to exit: ";
        std::string line;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear newline
        std::getline(std::cin, line);
        
        // Use istringstream to split tokens.
        std::istringstream iss(line);
        int itemChoice;
        if (!(iss >> itemChoice))
        {
            std::cout << "Invalid input. No valid number found.\n";
            return;
        }
        // Check if there is extra input
        std::string extra;
        if (iss >> extra)
        {
            std::cout << "Invalid input. Too many numbers provided.\n";
            return;
        }
        
        if (itemChoice < 0)
        {
            // Validate the index.
            if ((-itemChoice) > m_player.getInventory().getItemCount())
            {
                std::cout << "Invalid index. Try again.\n";
            }
            else
            {
                m_player.getInventory().removeItem(itemChoice);
            }
        } 
        else if (itemChoice == 0) 
        {
            return;
        }
        else
        {
            if (itemChoice > m_player.getInventory().getItemCount())
            {
                std::cout << "Invalid index. Try again.\n";
            }
            else
            {
                m_player.getInventory().useItem(itemChoice, m_player, &(m_combatSystem.getEnemy()));
            }
        }
    }
}