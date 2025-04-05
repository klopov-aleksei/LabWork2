#include "Character/PlayerCharacter.h"
#include <iostream>

void PlayerCharacter::displayStatus() const
{
    std::cout << m_name << " | HP: " << m_health 
              << " | AP: " << m_actionPoints
              << " | Mana: " << m_mana << "\n"
              << " | Strength: " << m_strength 
              << " | Intelligence: " << m_intelligence << "\n";
    std::cout << "Inventory: ";
    m_inventory.display();
}