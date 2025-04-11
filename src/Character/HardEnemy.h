#ifndef HARD_ENEMY_H
#define HARD_ENEMY_H

#include "MediumEnemy.h"

class HardEnemy : public MediumEnemy 
{
private: 
    void equipBackup() override;

    bool shouldBlock(const PlayerCharacter& player, double enemyHealthRatio);
    void performBlock();

public:
    HardEnemy();

    void performTurn(PlayerCharacter& player) override;
};

#endif