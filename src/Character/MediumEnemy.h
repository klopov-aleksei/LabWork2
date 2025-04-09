#ifndef MEDIUM_ENEMY_H
#define MEDIUM_ENEMY_H

#include "NPC.h"
#include "Equipment/Weapon.h"
#include "Equipment/Armor.h"
#include "Character/Character.h"
#include "Character/PlayerCharacter.h"
#include <memory>

class MediumEnemy : public NPC
{
private:
    int  m_ultraAttacksUsed; // Maximum 2 allowed per fight.
    int  m_turnsSinceUltra;
    bool m_hasBuff;
    Inventory m_inventory;
    
    // Helper functions implementing various actions.
    void performMeleeAttack(PlayerCharacter& player);
    void performSpellAttack(PlayerCharacter& player);
    void performUltraAttack(PlayerCharacter& player);
    void performHeal();
    void performBuff();
    void performRestoreMana();
    void performUseItem();
    
    int evaluateItem(const std::string& itemName);

    bool shouldUseUltra(double playerHealthRatio, double enemyHealthRatio);
    bool shouldHeal(double playerHealthRatio, double enemyHealthRatio);
    bool shouldRestoreMana();
    bool shouldBuff();
    bool shouldSpellCast();

public:
    MediumEnemy();
    virtual ~MediumEnemy() = default;
    
    // Perform the enemy AI turn against the given player.
    void performTurn(PlayerCharacter& player);
};

#endif