#ifndef NPC_H
#define NPC_H

#include "Character/Character.h"
#include "Equipment/Weapon.h"
#include "Equipment/Armor.h"
#include "Character/Character.h"
#include "Character/PlayerCharacter.h"
#include "Equipment/Inventory.h"
#include "Equipment/Item.h"

#include <memory>
#include <utility>
#include <string_view>

class NPC : public Character 
{
protected:
    bool m_hasBuff;
    bool m_hasEquippedBackup{};

public:
    NPC(std::string_view name, int strength, int intelligence, int agility, int mana, int health, int AP);

    void displayStatus() const override;

    virtual ~NPC() = default;
    virtual void performTurn(PlayerCharacter& player) = 0;

    bool shouldHeal(double playerHealthRatio, double enemyHealthRatio);
    bool shouldRestoreMana();
    bool shouldBuff();
    bool shouldSpellCast();

    virtual void performUltraAttack(PlayerCharacter& player);
    void performMeleeAttack(PlayerCharacter& player);
    void performSpellAttack(PlayerCharacter& player);
    void performHeal();
    void performBuff();
    void performRestoreMana();
};

#endif