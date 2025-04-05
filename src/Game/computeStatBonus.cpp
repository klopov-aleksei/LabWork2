#include "Character/Character.h"
#include "Constants.h"
#include <algorithm>

int computeStatBonus(const Character& attacker, int damage, bool isMelee)
{
    int baseStat{ isMelee ? attacker.getStrength() : attacker.getIntelligence() };
    
    double bonus{ 0.0 };
    for (const auto& stat : Constants::statThreshold)
    {
        bonus += (baseStat >= stat) ? Constants::high_bonus : Constants::low_bonus;
    }
    
    return damage * bonus;
}
