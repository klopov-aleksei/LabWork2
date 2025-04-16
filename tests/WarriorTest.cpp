#include "gtest/gtest.h"
#include "Character/Warrior.h"

TEST(WarriorTest, BlockSuccessActivatesDamageBuff) {
    Warrior warrior("TestWarrior");
    warrior.setBlockSuccess(true);
    warrior.resetActionPoints(); // Triggers damage buff
    EXPECT_TRUE(warrior.isDamageBuffActive());
}

TEST(WarriorTest, DamageBuffDeactivatesAfterReset) {
    Warrior warrior("TestWarrior");
    warrior.setBlockSuccess(true);
    warrior.resetActionPoints();
    warrior.resetDamageBuff();
    EXPECT_FALSE(warrior.isDamageBuffActive());
}