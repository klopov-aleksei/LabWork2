#include "gtest/gtest.h"
#include "Equipment/Weapon.h"

TEST(WeaponTest, DurabilityLossOnUse) {
    Weapon weapon("TestSword", 20, 50);
    weapon.takeDamage(10);
    EXPECT_EQ(weapon.getCurrentDurability(), 40);
}

TEST(WeaponTest, BaseDamageConsistency) {
    Weapon weapon("TestAxe", 25, 100);
    EXPECT_EQ(weapon.getBaseDamage(), 25);
}