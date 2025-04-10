#include "MediumEnemy.h"
#include "Skills/Investigate.h"
#include "Skills/MeleeAttack.h"
#include "Skills/SpellCast.h"
#include "Skills/Heal.h"
#include "Random.h"
#include "Constants.h"

#include <iostream>
#include <algorithm>

MediumEnemy::MediumEnemy(std::string_view name, int strength, int intelligence,
    int agility, int mana, int health, int AP)
    : NPC(name, strength, intelligence, agility, mana, health, AP)
    , m_ultraAttacksUsed{ 0 }
    , m_turnsSinceUltra{ 0 }
{   
    equipWeapon(std::make_unique<Weapon>("Frying Pan", 15, 20));
    equipArmor(std::make_unique<Armor>("Prison Armor", 20, 100));
}

void MediumEnemy::performTurn(PlayerCharacter &player)
{
    std::cout << "\n" << m_name << "'s turn begins.\n";
    m_turnsSinceUltra++;

    if (!m_hasEquippedBackup && (!getWeapon() || getWeapon()->isBroken())) 
    {
        equipWeapon(std::make_unique<Weapon>("Soul Reaper", 25, 50));
        std::cout << m_name << " equips Soul Reaper!\n";
        m_hasEquippedBackup = true;
    }

    while (m_actionPoints >= 2)
    {
        double playerHealthRatio = static_cast<double>(player.getHealth()) / player.getMaxHealth();
        double enemyHealthRatio  = static_cast<double>(m_health) / m_maxHealth;

        auto [bestItemPriority, bestIndex]{ evaluateInventory() };
        enum PriorityTier { HIGH, MEDIUM, LOW };
        PriorityTier tier{ (bestItemPriority > 40) ? HIGH : 
                            (bestItemPriority > 25) ? MEDIUM : LOW };

        bool canUseItem{ bestIndex != -1 && m_actionPoints >= 2 };
        
        if (shouldUseUltra(playerHealthRatio, enemyHealthRatio) && (m_actionPoints == m_maxActionPoints))
        {
            performUltraAttack(player);
        }
        else if (tier == HIGH && canUseItem) 
        {
            performUseItem(player, bestIndex);
        }
        else if (shouldHeal(playerHealthRatio, enemyHealthRatio) && m_actionPoints >= 3)
        {
            performHeal();
        }
        else if (tier == MEDIUM && canUseItem) 
        {
            performUseItem(player, bestIndex);
        }
        else if (shouldRestoreMana() && m_actionPoints >= 2)
        {
            performRestoreMana();
        }
        else if (tier == LOW && canUseItem) 
        {
            performUseItem(player, bestIndex);
        }
        else if (shouldBuff())
        {
            performBuff();
        }
        else if (m_actionPoints >= 4)
        {
            if (shouldSpellCast())
            {
                performSpellAttack(player);
            }
            else
            {
                performMeleeAttack(player);
            }
        }
        else
        {
            // No further viable actions.
            break;
        }
    }
    
    // At end of turn, acquires one random item.
    m_inventory.addItem(Investigate::createGenericItem());
    std::cout << m_name << "'s turn ends.\n";

    displayStatus();
}

bool MediumEnemy::shouldUseUltra(double playerHealthRatio, double enemyHealthRatio)
{
    // Ultra attack is allowed only if:
    // - At least 3 turns have passed since last ultra.
    // - Either the standard dynamic condition applies (player health below fixed threshold)
    //   and there was no better action, OR the enemy is in dire conditions:
    //   * enemy health < 15% and player's health <= 30%
    //   * weapon or armor durability is low
    if (m_turnsSinceUltra < 3 || m_ultraAttacksUsed >= 2)
    {
        return false;
    }
    
    double weaponCond{ 0.0 };
    double armorCond{ 0.0 };
    if (getWeapon())
    {
        weaponCond = static_cast<double>(getWeapon()->getCurrentDurability()) / getWeapon()->getMaxDurability();
    }
    if (getArmor())
    {
        armorCond = static_cast<double>(getArmor()->getCurrentDurability()) / getArmor()->getMaxDurability();
    }
    bool equipmentInTrouble = (weaponCond < 0.1) || (weaponCond < 0.2 && armorCond < 0.2);
    bool firstCondition = (playerHealthRatio < 0.5);
    bool secondCondition = (enemyHealthRatio < 0.15 && playerHealthRatio <= 0.3) 
                            || equipmentInTrouble;
    
    if (m_ultraAttacksUsed == 0)
        return firstCondition;
    else
        return secondCondition;
}

void MediumEnemy::performUltraAttack(PlayerCharacter& player)
{   
    int baseDamage = (getWeapon()) ? getWeapon()->getBaseDamage() : 0;
    int damage = static_cast<int>(baseDamage * 2.5);

    if (m_hasBuff)
    {
        damage = static_cast<int>(damage * 1.2);
        m_hasBuff = false;
    }
    
    std::cout << m_name << " unleashes an ULTRA ATTACK dealing " << damage << " damage, consuming all AP.\n";
    player.takeDamage(damage);
    takeActionPoints(m_actionPoints);
    m_ultraAttacksUsed++;
    m_turnsSinceUltra = 0;
}

void MediumEnemy::performUseItem(PlayerCharacter& player, int bestIndex) 
{
    if (bestIndex != -1 && m_actionPoints >= 2 && Random::get(0,100) < 85 ) 
    {
        m_inventory.useItem(bestIndex, *this, &player);
        std::cout << m_name << " uses an item.\n";
        takeActionPoints(2);
    }
    else 
    {
        std::cout << m_name << " decides not to use any item.\n";
    }
}

std::pair<int, int> MediumEnemy::evaluateInventory() const 
{
    int bestPriority = -1;
    int bestIndex = -1;
    
    for (int i = 0; i < m_inventory.getItemCount(); ++i) 
    {
        if (const Item* item = m_inventory[i+1]) // 1-based index
        {
            int priority = evaluateItem(*item);
            if (priority > bestPriority) 
            {
                bestPriority = priority;
                bestIndex = i+1;
            }
        }
    }
    return {bestPriority, bestIndex};
}

int MediumEnemy::evaluateItem(const Item& item) const
{
    int priority = 0;

    for (const auto& mod : item.getModifiers()) 
    {
        switch (mod.stat) 
        {
            case Stat::health:
                if (mod.value > 0) 
                {
                    double healthRatio = static_cast<double>(m_health) / m_maxHealth;
                    priority += (healthRatio < 0.5) ? mod.value * 10 : 0;
                } 
                else if (m_health > -mod.value + 10) 
                {
                    priority -= 30;
                }
                else priority -= 1000;
                break;
            case Stat::mana:
                if (mod.value > 0) 
                {
                    double manaRatio = static_cast<double>(m_mana) / m_maxMana;
                    priority += (manaRatio < 0.75) ? mod.value * 5 : 0;
                }
                else priority -= 1000;
                break;
            case Stat::maxHealth:
                priority += 0;
                break;
            case Stat::maxMana:
                if (mod.value > 0) 
                {
                    priority += mod.value * 7;
                }
                else priority -= 1000;
                break;
            case Stat::strength:
                priority += mod.value * 30;
                break;
            case Stat::intelligence:
                priority += mod.value * 30;
                break;
            case Stat::agility:
                priority += mod.value * 20;
                break;
            case Stat::actionPoints:
                priority += mod.value * 35;
                break;
            case Stat::repair:
                if (mod.target == Target::armor && getArmor()) 
                {
                    double armorCond = getArmor()->getCondition();
                    priority += (armorCond < 0.5) ? mod.value * 2 : 0;
                    if (mod.value < 0 && (-mod.value) > getArmor()->getCurrentDurability()) 
                        priority -= 1000;
                } 
                else if (mod.target == Target::weapon && getWeapon()) 
                {
                    double weaponCond = getWeapon()->getCondition();
                    priority += (weaponCond < 0.5) ? mod.value * 2 : 0;
                    if (mod.value < 0 && (-mod.value) > getWeapon()->getCurrentDurability()) 
                        priority -= 1000;
                }
                break;
            case Stat::damage:
                if (mod.target == Target::enemy) 
                {
                    priority += 15 + mod.value * 3;
                }
                if (mod.target == Target::self)
                {
                    if (m_health > -mod.value + 10) 
                    {
                        priority -= 30;
                    }
                    else priority -= 1000;
                }
                break;
            default:
                break;
        }
    }
    return priority;
}