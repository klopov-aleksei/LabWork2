#ifndef MEDIUM_ENEMY_H
#define MEDIUM_ENEMY_H

#include "NPC.h"

class MediumEnemy : public NPC
{
protected:
    Inventory m_inventory;
    int  m_ultraAttacksUsed; // Maximum 2 allowed per fight.
    int  m_turnsSinceUltra;
    
    void performUseItem(PlayerCharacter& player, int bestIndex);
    
    std::pair<int, int> evaluateInventory() const;
    int evaluateItem(const Item& item) const;

public:
    MediumEnemy(std::string_view name = "Sofiya", int strength = 6, int intelligence = 6, 
        int agility = 7, int mana = 50, int health = 300, int AP = 8);
    virtual ~MediumEnemy() = default;
    
    void performTurn(PlayerCharacter& player) override;

    bool shouldUseUltra(double playerHealthRatio, double enemyHealthRatio);
    void performUltraAttack(PlayerCharacter& player) override;
};

#endif