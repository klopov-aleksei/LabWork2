#include "EasyEnemy.h"

#include <iostream> 
#include <algorithm>

EasyEnemy::EasyEnemy()
    : NPC("Todd", 5, 5, 5, 30, 200, 7)
    , m_usedUltra{ false }
{   
    equipWeapon(std::make_unique<Weapon>("Spear", 10, 40));
    equipArmor(std::make_unique<Armor>("Black Magic Robe", 10, 50));
}

void EasyEnemy::equipBackup()
{
    if (!getWeapon() || getWeapon()->isBroken())
    {
        equipWeapon(std::make_unique<Weapon>("Gae Bolg", 20, 30));
        std::cout << m_name << " equips Gae Bolg!\n";
        m_hasEquippedBackup = true;
    }
}

void EasyEnemy::performTurn(PlayerCharacter& player)
{
    std::cout << "\n" << m_name << "'s turn begins.\n";
    m_hasBuff = false;

    if (!m_hasEquippedBackup)
        equipBackup();

    while (m_actionPoints >= 2)
    {
        double playerHealthRatio = static_cast<double>(player.getHealth()) / player.getMaxHealth();
        double enemyHealthRatio  = static_cast<double>(m_health) / m_maxHealth;

        if (!(m_usedUltra) && shouldUseUltra(playerHealthRatio, enemyHealthRatio))
        {
            performUltraAttack(player);
            m_usedUltra = true;
            break;
        }
        else if (shouldHeal(playerHealthRatio, enemyHealthRatio) && m_actionPoints >= 3)
        {
            performHeal();
        }
        else if (shouldRestoreMana() && m_actionPoints >= 2)
        {
            performRestoreMana();
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
    
    std::cout << m_name << "'s turn ends.\n";

    displayStatus();
}