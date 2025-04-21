#include "gtest/gtest.h"
#include "Equipment/Armor.h"
#include "Random.h"
#include "Constants.h"

class ArmorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Mock RNG with fixed seed for 55% reduction
        Random::mt = std::mt19937(42);
        // Advance to first relevant value
        Random::mt.discard(1);
    }
};

TEST_F(ArmorTest, TakesDamageAndCalculatesCondition) {
    Armor armor("TestArmor", 15, 100);
    armor.takeDamage(30);
    
    // 55% reduction: 30 * 0.55 = 16.5 → 16 
    EXPECT_EQ(armor.getCurrentDurability(), 84);
    EXPECT_FLOAT_EQ(armor.getCondition(), 0.84f);
}

TEST_F(ArmorTest, EffectiveDefenseScalesWithCondition) {
    Armor armor("TestArmor", 100, 200);
    armor.takeDamage(100);
    
    // 55% reduction: 100 * 0.55 = 55 damage
    // 200 - 55 = 145 durability → 72.5% condition
    EXPECT_EQ(armor.getEffectiveDefense(), 72); // 100 * 0.725
}