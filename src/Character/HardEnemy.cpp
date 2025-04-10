#include "HardEnemy.h"

HardEnemy::HardEnemy()
    : MediumEnemy("Nyarlathotep", 8, 8, 10, 60, 300, 9)
{   
    equipWeapon(std::make_unique<Weapon>("Chaos Blade", 22, 22));
    equipArmor(std::make_unique<Armor>("Elite Knight Armor", 25, 100));
}