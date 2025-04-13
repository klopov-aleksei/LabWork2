#include "gtest/gtest.h"
#include "Skills/MeleeAttack.h"
#include "Character/Warrior.h"
#include "Character/Character.h"
#include "Equipment/Weapon.h"

class TestTarget : public Character {
public:
    TestTarget() : Character("TestTarget", 5, 5, 5, 50, 100, 10) {}
    void displayStatus() const override {}
};

TEST(MeleeAttackTest, WeaponDamage) {
    Warrior warrior("Arthur");
    TestTarget target;
    auto weapon = std::make_unique<Weapon>("Sword", 20, 50);
    warrior.equipWeapon(std::move(weapon));
    
    MeleeAttack attack;
    attack.execute(warrior, target);  // Now valid
    EXPECT_LT(target.getHealth(), 100);
    EXPECT_LT(warrior.getWeapon()->getCurrentDurability(), 50);
}

TEST(MeleeAttackTest, BlockDamageBuff) {
    Warrior warrior{ "Arthur" };
    TestTarget target;
    auto weapon = std::make_unique<Weapon>("Sword", 20, 50);
    warrior.equipWeapon(std::move(weapon));
    
    warrior.setBlockSuccess(true);
    warrior.resetActionPoints();
    
    MeleeAttack attack;
    attack.execute(warrior, target);
    EXPECT_FALSE(warrior.isDamageBuffActive());
}