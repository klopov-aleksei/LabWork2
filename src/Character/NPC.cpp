#include "NPC.h"
#include <iostream>
#include <iomanip>

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
                  << ' ' << std::fixed << std::setprecision(2)
                  << (armor->getCondition() * 100) << '%'
                  << " (" << armor->getCurrentDurability()
                  << "/" << armor->getMaxDurability() << ")\n";
    }
    
    std::cout << "====================\n";
}