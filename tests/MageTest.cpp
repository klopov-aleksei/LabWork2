#include "gtest/gtest.h"
#include "Character/Mage.h"

TEST(MageTest, ManaRegeneration) 
{
    Mage mage("Gandalf");

    mage.increaseMaxMana(10);
    
    for (int i = 0; i <= 5; ++i) 
    {
        mage.startNewTurn();
    }
    
    EXPECT_EQ(mage.getMana(), 60);  // 50 base + 10 regeneration
}