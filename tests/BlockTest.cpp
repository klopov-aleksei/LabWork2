#include "gtest/gtest.h"
#include "Skills/Block.h"
#include "Character/Warrior.h"
#include "Constants.h"

TEST(BlockTest, BasicBlocking) {
    Warrior warrior{ "Arthur" };
    warrior.resetActionPoints();
    Block block;
    
    block.execute(warrior);
    EXPECT_TRUE(warrior.isBlocking());
    EXPECT_EQ(warrior.getActionPoints(), 10 - Constants::block_cost);
}

TEST(BlockTest, EasyBlockReduction) {
    Warrior warrior{ "Arthur" };
    warrior.reduceBlockCost(); // Enable EasyBlock
    warrior.resetActionPoints();
    Block block;
    
    block.execute(warrior);
    EXPECT_EQ(warrior.getActionPoints(), 7);
}