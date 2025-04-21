#include "gtest/gtest.h"
#include "Skills/Concentrate.h"
#include "Character/Mage.h"
#include "Constants.h"

TEST(ConcentrateTest, BasicConcentration) {
    Mage mage{ "Gandalf" };
    mage.resetActionPoints();
    mage.increaseMaxMana(10);

    Concentrate concentrate;
    concentrate.execute(mage);
    EXPECT_EQ(mage.getMana(), 60);
    EXPECT_EQ(mage.getActionPoints(), 10 - Constants::conc_cost);

    mage.resetActionPoints();
    EXPECT_EQ(mage.getActionPoints(), 11);
}

TEST(ConcentrateTest, MonkTrainingBonus) {
    Mage mage{ "Gandalf" };
    mage.boostConcentration(); // enable Monk Training
    mage.resetActionPoints();
    mage.increaseMaxMana(20);

    Concentrate concentrate;
    concentrate.execute(mage);
    EXPECT_EQ(mage.getMana(), 70);
    EXPECT_EQ(mage.getActionPoints(), 10 - (Constants::conc_cost - 1));
}