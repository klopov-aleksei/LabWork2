#include "HardEnemy.h"
#include "Skills/Block.h"
#include "Skills/Investigate.h"
#include "Character/Warrior.h"
#include "Constants.h"
#include "Random.h"
#include "Constants.h"

#include <iostream> 
#include <algorithm>

HardEnemy::HardEnemy()
    : MediumEnemy("Nyarlathotep", 8, 8, 10, 60, 300, 9)
{   
    equipWeapon(std::make_unique<Weapon>("Chaos Blade", 22, 22));
    equipArmor(std::make_unique<Armor>("Elite Knight Armor", 25, 100));
}

void HardEnemy::equipBackup()
{
    if (!getWeapon() || getWeapon()->isBroken()) 
    {
        equipWeapon(std::make_unique<Weapon>("Frayed Blade", 30, 50));
        std::cout << m_name << " equips Frayed Blade!\n";
        m_hasEquippedBackup = true;
    }
}

bool HardEnemy::shouldBlock(const PlayerCharacter& player, double enemyHealthRatio) 
{ 
    int priority{ 0 };
    if (getArmor())
    {
        double cond = getArmor()->getCondition();
        if (cond < 0.5) priority += 10;
        if (cond < 0.25) priority += 15;
    }
    else
    {
        priority += 30;
    }

    if (enemyHealthRatio < 0.5) priority += 10;
    if (enemyHealthRatio < 0.25) priority += 15;

    if (auto* warrior = dynamic_cast<const Warrior*>(&player))
    {
        if (warrior->isDamageBuffActive())
            priority += 45;
    }

    int playerAttacks{ player.getAttackCount() };
    if (playerAttacks > 2)
        priority -= 45;
    else if (playerAttacks == 2)
        priority += 5;
    else if (playerAttacks <= 1)
        priority += 15;

    return (Random::get(0, 100) <= priority) && m_actionPoints == Constants::block_cost;
}

void HardEnemy::performBlock()
{
    Block().execute(*this);
}

void HardEnemy::performTurn(PlayerCharacter& player)
{
    m_turnsSinceUltra++;
    std::cout << "\n" << m_name << "'s turn begins.\n";
    m_hasBuff = false;

    if (!m_hasEquippedBackup)
        equipBackup();

    while (m_actionPoints >= 1)
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
            m_ultraAttacksUsed++;
            m_turnsSinceUltra = 0;
            break;
        }
        else if (shouldBlock(player, enemyHealthRatio))
        {
            performBlock();
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
            if (!(shouldBlock(player, enemyHealthRatio)) || (Random::get(0,100) <= 20) || m_hasBuff)
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
        }
        else
        {
            break;
        }
    }
    
    // At end of turn, acquires one random item.
    m_inventory.addItem(Investigate::createGenericItem());
    std::cout << m_name << "'s turn ends.\n";

    displayStatus();
}