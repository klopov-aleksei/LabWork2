#include "Character/Character.h"
#include "Character/PlayerCharacter.h"
#include "Constants.h"
#include <algorithm>

int computeStatBonus(const Character& attacker, int damage, bool isMelee)
{   
    int str_bonus{ 0 };
    if (auto* pc = dynamic_cast<const PlayerCharacter* const>(&attacker)) 
    {
        str_bonus = pc->getStrengthBonus();
    }

    int baseStat{ isMelee ? attacker.getStrength() + str_bonus : attacker.getIntelligence() };
    double bonus{ 0.0 };
    for (const auto& stat : Constants::statThreshold)
    {
        bonus += (baseStat >= stat) ? Constants::high_bonus : Constants::low_bonus;
    }
    
    return damage * bonus;
}
