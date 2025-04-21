#include "Character/Mage.h"

Mage::Mage(std::string_view name) 
    : PlayerCharacter(name, 7, 50) 
{ 
    enableSpellCast(); 
}

void Mage::startNewTurn() 
{ 
    ++m_turnCounter; 
    if (m_turnCounter % 5 == 0) 
    {
        increaseMana(10);
        std::cout << getName() << " regenerates 10 mana every 5th turn!\n";
    }
}