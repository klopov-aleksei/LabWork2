#include "MediumEnemy.h"
#include "Random.h"
#include "Constants.h"
#include <iostream>
#include <algorithm>

MediumEnemy::MediumEnemy()
    : NPC("Sofiya", 6, 6, 7, 50)
{
    m_health            = 300;
    m_maxHealth         = 300;
    m_actionPoints      = 8;
    m_maxActionPoints   = 8;
    m_ultraAttacksUsed  = 0;
    m_turnsSinceUltra   = 0;
    m_hasBuff           = false;
    
    // Equip the initial weapon and armor.
    // Initial weapon: 15 damage, 20 durability.
    equipWeapon(std::make_unique<Weapon>("Medium Enemy Weapon", 15, 20));
    // Initial armor: 20 defense, 50 durability.
    equipArmor(std::make_unique<Armor>("Medium Enemy Armor", 20, 50));
}

void MediumEnemy::performTurn(PlayerCharacter &player)
{
    std::cout << "\n" << m_name << "'s turn begins.\n";

    m_turnsSinceUltra++;
    while (m_actionPoints >= 2)
    {
        double playerHealthRatio = static_cast<double>(player.getHealth()) / player.getMaxHealth();
        double enemyHealthRatio  = static_cast<double>(m_health) / m_maxHealth;
        
        // Flags to decide which action to perform.
        bool useUltra       = shouldUseUltra(playerHealthRatio, enemyHealthRatio);
        bool useHeal        = shouldHeal(playerHealthRatio, enemyHealthRatio);
        bool useRestoreMana = shouldRestoreMana();
        bool useBuff        = shouldBuff();
        bool useSpellAttack = shouldSpellCast();
        
        // Action priority: Ultra > Heal > Restore Mana > Item > Buff > Attack.
        if (useUltra && (m_actionPoints == m_maxActionPoints))
        {
            performUltraAttack(player);
        }
        else if (useHeal && m_actionPoints >= 3)
        {
            performHeal();
        }
        else if (useRestoreMana && m_actionPoints >= 2)
        {
            performRestoreMana();
        }
        else if (!m_inventory.isEmpty() && m_actionPoints >= 2)
        {
            performUseItem();
        }
        else if (useBuff && m_actionPoints >= 2)
        {
            performBuff();
        }
        else if (m_actionPoints >= 4)
        {
            if (useSpellAttack)
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
    m_inventory.addItem(std::make_unique<Item>("Random Investigate Item", Rarity::common));
    std::cout << m_name << "'s turn ends.\n";
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


bool MediumEnemy::shouldHeal(double playerHealthRatio, double enemyHealthRatio)
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

bool MediumEnemy::shouldRestoreMana()
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

bool MediumEnemy::shouldBuff()
{
    if (!m_hasBuff && m_actionPoints >= 2)
    {
        if (Random::get(0, 100) < 40)
            return true;
    }
    return false;
}

bool MediumEnemy::shouldSpellCast()
{
    if (m_mana >= 20 && m_actionPoints >= 4)
    {
        if (Random::get(0, 100) < 50)
            return true;
    }
    return false;
}

void MediumEnemy::performMeleeAttack(PlayerCharacter& player)
{
    const int cost = 4;
    if (m_actionPoints < cost)
    {
        return;
    }
    int baseDamage = (getWeapon()) ? getWeapon()->getBaseDamage() : 0;
    
    if (m_hasBuff)
    {
        baseDamage = static_cast<int>(baseDamage * 1.2);
        m_hasBuff = false;
    }
    
    std::cout << m_name << " performs a melee attack dealing " << baseDamage << " damage.\n";
    player.takeDamage(baseDamage);
    takeActionPoints(cost);
}

void MediumEnemy::performSpellAttack(PlayerCharacter& player)
{
    const int cost = 4;
    if (m_actionPoints < cost || m_mana < 20)
    {
        return;
    }
    
    // Damage calculation: 20 constant damage plus 50% of current weapon damage.
    int weaponDamage = 0;
    if (getWeapon())
    {
        weaponDamage = getWeapon()->getBaseDamage();
    }
    int damage = 20 + static_cast<int>(0.5 * weaponDamage);
    
    // Apply buff if active.
    if (m_hasBuff)
    {
        damage = static_cast<int>(damage * 1.2);
        m_hasBuff = false;
    }
    
    std::cout << m_name << " casts a spell attack dealing " << damage << " damage (Cost: 20 mana).\n";
    player.takeDamage(damage);
    m_mana -= 20;
    takeActionPoints(cost);
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
    m_ultraAttacksUsed++;
    m_turnsSinceUltra = 0;
    takeActionPoints(m_actionPoints); // Consumes all remaining AP.
}

void MediumEnemy::performHeal()
{
    const int cost = 3;
    if (m_actionPoints < cost)
    {
        return;
    }
    
    increaseHealth(Constants::healAmount);
    std::cout << m_name << " heals for " << Constants::healAmount << " HP.\n";
    takeActionPoints(cost);
}

void MediumEnemy::performBuff()
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

void MediumEnemy::performRestoreMana()
{
    const int cost = 2;
    if (m_actionPoints < cost)
    {
        return;
    }
    
    increaseMana(15);
    std::cout << m_name << " restores 15 mana.\n";
    takeActionPoints(cost);
}

void MediumEnemy::performUseItem()
{
    // Evaluate each item in inventory (simulate by item name for now).
    // For a real implementation, you would inspect each Item's modifiers.
    // Here we use a simplified evaluation based on the item name.
    int bestItemPriority = -1000;
    int bestItemIndex = -1;
    
    // Iterate over items to determine usefulness.
    for (int i = 0; i < m_inventory.getItemCount(); i++)
    {
        int priority = evaluateItem("dummy"); // Replace "dummy" with actual item identifier.
        if (priority > bestItemPriority)
        {
            bestItemPriority = priority;
            bestItemIndex = i;
        }
    }
    
    if (bestItemIndex >= 0 && m_actionPoints >= 2)
    {
        // Use the chosen item. This costs 2 AP.
        std::cout << m_name << " uses an item from inventory based on its effectiveness.\n";
        m_inventory.useItem(bestItemIndex + 1, *this);
        takeActionPoints(2);
    }
    else
    {
        // No item is effective to use this turn.
        std::cout << m_name << " decides not to use any stored item this turn.\n";
    }
}

int MediumEnemy::evaluateItem(const std::string& itemName)
{
    // A stub function for item evaluation.
    // In a complete implementation, inspect the item's type and modifiers.
    // Return a priority value: higher means more useful under current conditions.
    // For example:
    // - If enemy health is low, a healing item should get a high score.
    // - If enemy mana is low, a mana-restoring item should get a high score.
    // Here we return a dummy value.
    return Random::get(0, 100);
}