#ifndef CHARACTER_CREATION_H
#define CHARACTER_CREATION_H

#include "Character/PlayerCharacter.h"
#include "Character/Warrior.h"
#include "Character/Mage.h"
#include "Equipment/Weapon.h"
#include "Equipment/Armor.h"
#include "Skills/Skill.h"
#include "Skills/MeleeAttack.h"
#include "Skills/SpellCast.h"
#include "Equipment/Inventory.h"
#include "Equipment/Item.h"

#include <iostream>
#include <memory>

class CharacterCreation 
{
public:
    std::unique_ptr<PlayerCharacter> createCharacter();

protected:
    static std::string ChooseName();
    static std::unique_ptr<PlayerCharacter> ChooseClass(std::string_view name);
    static void CustomizeStats(PlayerCharacter& character);
    static void ChooseWeapon(PlayerCharacter& character);
    static void ChooseArmor(PlayerCharacter& character);
    static void ChooseSkills(PlayerCharacter& character);
    static void ChooseInventory(PlayerCharacter& character);
};

#endif