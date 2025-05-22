#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "Character.h"
#include "Equipment/Inventory.h"
#include "Skills/Skill.h"

class PlayerCharacter : public Character 
{
private:
    Inventory m_inventory;

    bool hasSpellCastSkill{ false };
    bool canHeal{ false };
    bool monkTraining{ false };
    bool easyBlock{ false };

    int investigateCost{ Constants::invest_cost };
    int strengthBonus{ 0 };
    
public:
    PlayerCharacter(): Character() { }
    PlayerCharacter(std::string_view name, int agility, int mana)
        : Character(name, agility, mana)
    {
    }

    void displayStatus() const override;

    Inventory& getInventory() { return m_inventory; }
    const Inventory& getInventory() const { return m_inventory; } 

    void enableSpellCast () { hasSpellCastSkill = true; }
    void unlockHealing() { canHeal = true; }
    void boostConcentration() { monkTraining = true; }
    void reduceBlockCost() { easyBlock = true; }

    bool canUseSpell () const { return hasSpellCastSkill; }
    bool hasHealing() const { return canHeal; }
    bool hasMonkTraining() const { return monkTraining; }
    bool hasEasyBlock() const { return easyBlock; }

    void updateArmorBonuses();

    int getInvestigateCost() const { return investigateCost; }
    int getStrengthBonus() const { return strengthBonus; }
};

#endif