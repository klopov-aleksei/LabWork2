#include "gtest/gtest.h"
#include "Game/computeStatBonus.h"
#include "Character/PlayerCharacter.h"
#include "Character/Warrior.h"

TEST(ComputeStatBonusTest, StrengthBonusCalculation) {
    Warrior warrior("Test");
    warrior.increaseStrength(5);
    int bonus = computeStatBonus(warrior, 10, true);
    EXPECT_GT(bonus, 0);
}

TEST(ComputeStatBonusTest, ZeroStatBonus) {
    PlayerCharacter pc("Test", 5, 50);
    pc.setStats(0, 0);
    int bonus = computeStatBonus(pc, 10, true);
    EXPECT_LE(bonus, 0);
}