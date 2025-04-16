#include "gtest/gtest.h"
#include "Equipment/Item.h"
#include "Character/Character.h"

class TestCharacter : public Character {
public:
    TestCharacter() : Character("TestChar", 5, 5, 5, 50, 100, 10) {}
    void displayStatus() const override {}
};

TEST(ItemTest, StatModifierApplication) {
    TestCharacter character;
    std::vector<StatModifier> modifiers {
        {Stat::health, 20, Target::self},
        {Stat::strength, 2, Target::self}
    };
    
    character.increaseHealth(-30); // Now 70/100
    Item potion("Strength Potion", Rarity::common, modifiers);
    potion.use(character, nullptr);
    
    EXPECT_EQ(character.getHealth(), 90); // 70 + 20
    EXPECT_EQ(character.getStrength(), 7); // 5 base + 2
}

TEST(ItemTest, NegativeModifierClamping) {
    TestCharacter character;
    std::vector<StatModifier> modifiers {
        {Stat::health, -80, Target::self} 
    };
    
    Item cursedItem("Cursed Amulet", Rarity::rare, modifiers);
    cursedItem.use(character);
    
    EXPECT_EQ(character.getHealth(), 20);
}