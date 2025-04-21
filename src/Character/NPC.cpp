#include "NPC.h"
#include "Skills/Investigate.h"
#include "Skills/MeleeAttack.h"
#include "Skills/SpellCast.h"
#include "Skills/Heal.h"
#include "Random.h"
#include "Constants.h"

#include <iostream>
#include <algorithm>
#include <iomanip>

NPC::NPC(std::string_view name, int strength, int intelligence, int agility, int mana, int health, int AP)
  : Character(name, strength, intelligence, agility, mana, health, AP)
  , m_hasBuff{ false }
  , m_hasEquippedBackup{ false } 
{
}

void NPC::displayStatus() const 
{
    std::cout << "\n=== Enemy Status ===\n";
    std::cout << "Name: " << getName() << "\n"
              << "Health: " << getHealth() << "/" << getMaxHealth() << "\n"
              << "Mana: " << m_mana << "/" << m_maxMana << "\n"
              << "Strength: " << m_strength << "\n"
              << "Intelligence: " << m_intelligence << "\n"
              << "Agility: " << m_agility << "\n";

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

bool NPC::shouldUseUltra(double playerHealthRatio, double enemyHealthRatio)
{
    return playerHealthRatio < 0.4  && enemyHealthRatio < 0.5 && m_actionPoints == m_maxActionPoints;
}

bool NPC::shouldHeal(double playerHealthRatio, double enemyHealthRatio)
{
    // Healing is an option if enemy health is below 50%.
    // But if the player's health is also low, offensive actions might be preferred.
    if (enemyHealthRatio < 0.5)
    {
        if (Random::get(0, 100) < 50)
            return true;
        else if (playerHealthRatio < 0.3)
            return (Random::get(0, 100) < 25);
    }
    return false;
}

bool NPC::shouldRestoreMana()
{
    // If mana is less than 20, or if mana is not full (<= max - 15),
    // increase chance to restore.
    if (m_mana <= (m_maxMana - 15))
    {
        if (Random::get(0, 100) < 40)
            return true;
        else if (m_mana < 20)
            return (Random::get(0,100) < 80);
    }
    return false;
}

bool NPC::shouldBuff()
{
    if (!m_hasBuff && m_actionPoints >= 6)
    {
        if (Random::get(0, 100) < 40)
            return true;
    }
    return false;
}

bool NPC::shouldSpellCast()
{
    if (m_mana >= 30 && m_actionPoints >= 4 )
    {
        if (const Weapon* weapon = getWeapon())
        {
            int chance{ Random::get(0, 100) };
            if (m_hasEquippedBackup)
            {
                if (weapon->getCondition() < 0.5) 
                {
                    chance += 25;
                }
            }
            else
            {
                chance -= 5;
            }

            if (chance > 50)
                return false;
        }
        return true;
    }
    return false;
}

void NPC::performUltraAttack(PlayerCharacter& player)
{   
    int baseDamage = (getWeapon()) ? getWeapon()->getBaseDamage() : 0;
    int damage = static_cast<int>(baseDamage * 2.8);
    
    std::cout << m_name << " unleashes an ULTRA ATTACK dealing " << damage << " damage, consuming all AP.\n";
    player.takeDamage(damage);
    takeActionPoints(m_actionPoints); // Consumes all remaining AP.
}

void NPC::performMeleeAttack(PlayerCharacter& player)
{
    int damage = (getWeapon()) ? getWeapon()->getBaseDamage() : 0;
    if (m_hasBuff)
    {
        damage = static_cast<int>(damage * 1.2);
        m_hasBuff = false;
    }

    MeleeAttack meleeAttack{ damage, 4 };
    meleeAttack.execute(*this, player);
}

void NPC::performSpellAttack(PlayerCharacter& player)
{   
    int weaponDamage{ 0 };
    if (getWeapon())
    {
        weaponDamage = getWeapon()->getBaseDamage();
    }
    int damage = 16 + static_cast<int>(0.5 * weaponDamage);
    if (m_hasBuff)
    {
        damage = static_cast<int>(damage * 1.2);
        m_hasBuff = false;
    }

    SpellCast spellCast{ 30, damage, 4 };
    spellCast.execute(*this, player);
}

void NPC::performHeal()
{
    Heal heal{ 3 };
    heal.execute(*this);
}

void NPC::performBuff()
{
    const int cost = 2;
    if (m_actionPoints < cost)
    {
        return;
    }
    
    m_hasBuff = true;
    std::cout << m_name << " increases damage for the next attack by 20%.\n";
    takeActionPoints(cost);
}

void NPC::performRestoreMana()
{
    const int cost = 2;
    if (m_actionPoints < cost)
    {
        return;
    }
    
    std::cout << m_name << " restores mana.\n";
    increaseMana(15);
    takeActionPoints(cost);
}