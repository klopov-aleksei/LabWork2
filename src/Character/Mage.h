#ifndef MAGE_H
#define MAGE_H

#include "PlayerCharacter.h"

class Mage : public PlayerCharacter 
{
private:
    int m_turnCounter{ 0 };

public:
    Mage(std::string_view name);

    void startNewTurn();
    int getTurnCounter() const { return m_turnCounter; }
};

#endif