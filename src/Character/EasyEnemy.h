#ifndef EASY_ENEMY_H
#define EASY_ENEMY_H

#include "Character/NPC.h"

class EasyEnemy : public NPC 
{
private:
    bool m_usedUltra{ false };

public:
    EasyEnemy();
};

#endif