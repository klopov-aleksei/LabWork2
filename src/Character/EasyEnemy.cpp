#include "EasyEnemy.h"

EasyEnemy::EasyEnemy()
    : NPC("Todd", 5, 5, 5, 30, 200, 6)
    , m_usedUltra{ false }
{   
    equipWeapon(std::make_unique<Weapon>("Spear", 10, 20));
    equipArmor(std::make_unique<Armor>("Black Magic Robe", 10, 50));
}