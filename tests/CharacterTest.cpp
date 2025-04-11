#include "gtest/gtest.h"
#include "Character/Character.h"
#include "Character/PlayerCharacter.h"
#include "Character/Mage.h"
#include "Character/Warrior.h"

#include "gtest/gtest.h"
#include "Character/Character.h"
#include "Equipment/Weapon.h"

class TestCharacter : public Character {
public:
    TestCharacter(std::string_view name, int strength, int intelligence, 
                int agility, int mana, int health, int actionPoints)
        : Character(name, strength, intelligence, agility, mana, health, actionPoints) {}
    
    void displayStatus() const override {
    }
};

TEST(CharacterTest, StatManagement) {
    TestCharacter character("Test", 5, 5, 5, 50, 100, 10);
    
    character.setStats(8, 12);
    EXPECT_EQ(character.getStrength(), 8);
    EXPECT_EQ(character.getIntelligence(), 12);
    
    character.increaseStrength(2);
    EXPECT_EQ(character.getStrength(), 10);
}

TEST(CharacterTest, CombatActions) {
    TestCharacter character("Test", 10, 10, 5, 50, 100, 10);
    
    character.setBlocking(true);
    EXPECT_TRUE(character.isBlocking());
    
    character.resetActionPoints();
    EXPECT_EQ(character.getActionPoints(), 10);
    
    character.takeDamage(20);
    EXPECT_EQ(character.getHealth(), 80);
}

TEST(CharacterTest, EquipmentManagement) {
    TestCharacter character("Test", 5, 5, 5, 50, 100, 10);
    auto weapon = std::make_unique<Weapon>("Sword", 15, 30);
    
    character.equipWeapon(std::move(weapon));
    ASSERT_NE(character.getWeapon(), nullptr);
    EXPECT_EQ(character.getWeapon()->getName(), "Sword");
}