#include "gtest/gtest.h"
#include "Skills/Heal.h"
#include "Character/PlayerCharacter.h"
#include "Constants.h"

TEST(HealTest, BasicHealing) {
    PlayerCharacter pc{ "Healer", 5, 50 };
    pc.increaseHealth(-50);

    Heal heal;
    heal.execute(pc);
    EXPECT_EQ(pc.getHealth(), 70);
    EXPECT_EQ(pc.getActionPoints(), 10 - Constants::heal_cost);
}

TEST(HealTest, InsufficientAP) {
    PlayerCharacter pc{ "Healer", 5, 50 };
    pc.takeActionPoints(9);
    pc.increaseHealth(-70);
    
    Heal heal;
    heal.execute(pc);
    EXPECT_EQ(pc.getHealth(), 30);
}