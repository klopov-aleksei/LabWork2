#include "DamageCalculator.h"
#include "Equipment/Armor.h"
#include "Random.h"
#include "Constants.h"

#include <algorithm>

void calculateDamage(DamageCalculator& dmgCalc, Character& target, 
    int baseDamage, int statBonus, int attackCount)
{
    int randomBonus{ Random::get(Constants::min_attack_bonus, Constants::max_attack_bonus) };
    double multiplier{ (attackCount >= Constants::critThreshold) ? 
        Random::get(Constants::min_crit_multiplier, Constants::max_crit_multiplier) / 100.0 : 1.0 };
    int rawDamage{ static_cast<int>((baseDamage + statBonus + randomBonus) * multiplier) };
    
    double blockFactor{ 1.0 };
    if (target.isBlocking())
    {
        blockFactor -= Random::get(Constants::min_block_reduce, Constants::max_block_reduce) / 100.0;
        target.setBlocking(false);
        std::cout << target.getName() << " blocks the attack, reducing the damage!\n";
    }

    dmgCalc.m_finalDamage = static_cast<int>(rawDamage * blockFactor);

    if (dmgCalc.m_isSpell) 
    {
        if (target.getArmor()) 
        {
            // Spell damage only to armor
            dmgCalc.m_armorDamage = std::max(0, dmgCalc.m_finalDamage);
            dmgCalc.m_finalDamage = 0;
        } 
        else 
        {
            // No armor - damage health directly
            dmgCalc.m_armorDamage = 0;
        }
        dmgCalc.m_isSpell = false;
    } 
    else 
    {
        // Melee/items:
        int armorDefense = target.getArmor() ? 
            target.getArmor()->getEffectiveDefense() : 0;
        dmgCalc.m_armorDamage = std::max(0, dmgCalc.m_finalDamage);
        dmgCalc.m_finalDamage = std::max(0, dmgCalc.m_armorDamage - armorDefense);
    }
}
