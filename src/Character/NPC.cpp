#include "NPC.h"
#include <iostream>

void NPC::displayStatus() const 
{
    std::cout << "\n=== Enemy Status ===\n";
    std::cout << "Name: " << getName() << "\n"
              << "Health: " << getHealth() << "/" << getMaxHealth() << "\n";

    if (auto weapon = getWeapon()) 
    {
        std::cout << "Weapon: " << weapon->getName()
                  << " (" << weapon->getCurrentDurability()
                  << "/" << weapon->getMaxDurability() << ")\n";
    }
    
    if (auto armor = getArmor()) 
    {
        std::cout << "Armor: " << armor->getName()
                  << " (" << armor->getCurrentDurability()
                  << "/" << armor->getMaxDurability() << ")\n";
    }
    
    std::cout << "====================\n";
}