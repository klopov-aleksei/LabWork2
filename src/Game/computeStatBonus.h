#ifndef COMPUTE_STAT_BONUS_H
#define COMPUTE_STAT_BONUS_H

class Character;

int computeStatBonus(const Character& attacker, int damage, bool isMelee);

#endif