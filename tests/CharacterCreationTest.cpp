#include "gtest/gtest.h"
#include "Game/CharacterCreation.h"
#include "Character/Warrior.h"
#include "Character/Mage.h"
#include "Equipment/Weapon.h"
#include "Equipment/Armor.h"
#include <sstream>

class TestableCharacterCreation : public CharacterCreation {
public:
    using CharacterCreation::ChooseClass;
    using CharacterCreation::CustomizeStats;
    using CharacterCreation::ChooseWeapon;
    using CharacterCreation::ChooseArmor;
    using CharacterCreation::ChooseSkills;
    using CharacterCreation::ChooseInventory;
};

class CharacterCreationTest : public ::testing::Test {
protected:
    std::streambuf* origCinBuf;
    std::stringstream input;

    void SetUp() override {
        origCinBuf = std::cin.rdbuf();
        std::cin.rdbuf(input.rdbuf());
    }

    void TearDown() override {
        std::cin.rdbuf(origCinBuf);
    }
};

TEST_F(CharacterCreationTest, ChooseClassCreatesWarrior) {
    input.str("1\n");
    auto pc = TestableCharacterCreation::ChooseClass("TestWarrior");
    ASSERT_NE(dynamic_cast<Warrior*>(pc.get()), nullptr);
}

TEST_F(CharacterCreationTest, ChooseClassCreatesMage) {
    input.str("2\n");
    auto pc = TestableCharacterCreation::ChooseClass("TestMage");
    ASSERT_NE(dynamic_cast<Mage*>(pc.get()), nullptr);
}

TEST_F(CharacterCreationTest, CustomizeStatsDistributesPoints) {
    input.str("8\n2\n");
    Warrior warrior("Test");
    TestableCharacterCreation::CustomizeStats(warrior);
    EXPECT_EQ(warrior.getStrength(), 8);
    EXPECT_EQ(warrior.getIntelligence(), 2);
}

TEST_F(CharacterCreationTest, ChooseWeaponEquipsSword) {
    input.str("1\n");
    Warrior warrior("Test");
    TestableCharacterCreation::ChooseWeapon(warrior);
    ASSERT_NE(warrior.getWeapon(), nullptr);
    EXPECT_EQ(warrior.getWeapon()->getName(), "Sword");
}

TEST_F(CharacterCreationTest, ChooseArmorEquipsLightArmor) {
    input.str("1\n");
    Warrior warrior("Test");
    TestableCharacterCreation::ChooseArmor(warrior);
    ASSERT_NE(warrior.getArmor(), nullptr);
    EXPECT_EQ(warrior.getArmor()->getName(), "Light Armor");
}

TEST_F(CharacterCreationTest, ChooseSkillEnablesHealing) {
    input.str("1\n");
    Warrior warrior("Test");
    TestableCharacterCreation::ChooseSkills(warrior);
    EXPECT_TRUE(warrior.hasHealing());
}

TEST_F(CharacterCreationTest, ChooseInventoryAddsItem) {
    input.str("1\n");
    Warrior warrior("Test");
    TestableCharacterCreation::ChooseInventory(warrior);
    EXPECT_EQ(warrior.getInventory().getItemCount(), 2); // Includes default potion
}