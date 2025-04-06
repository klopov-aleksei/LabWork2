#include "Character/PlayerCharacter.h"
#include <iostream>

void PlayerCharacter::displayStatus() const
{
    std::cout << m_name << " | HP: " << m_health << "/" << m_maxHealth
              << " | AP: " << m_actionPoints << "/" << m_maxActionPoints
              << " | Mana: " << m_mana << "/" << m_maxMana << "\n"
              << " | Strength: " << m_strength 
              << " | Intelligence: " << m_intelligence 
              << " | Agility: " << m_agility << "\n";
    if (equippedWeapon) 
    {
        std::cout << "Weapon: " << equippedWeapon->getName() 
                  << " (" << equippedWeapon->getCurrentDurability() 
                  << "/" << equippedWeapon->getMaxDurability() << ")\n";
    } 
    else 
    {
        std::cout << "Weapon: None\n";
    }
    if (equippedArmor) 
    {
        std::cout << "Armor: " << equippedArmor->getName() 
                  << " (" << equippedArmor->getCurrentDurability() 
                  << "/" << equippedArmor->getMaxDurability() << ")\n";
    } 
    else 
    {
        std::cout << "Armor: None\n";
    }
    m_inventory.display();
}