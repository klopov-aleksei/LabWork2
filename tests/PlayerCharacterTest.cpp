#include "gtest/gtest.h"
#include "Character/PlayerCharacter.h"

TEST(PlayerCharacterTest, InventoryManagement) 
{
    PlayerCharacter pc;
    auto item = std::make_unique<Item>("Potion", Rarity::common);
    
    EXPECT_TRUE(pc.getInventory().isEmpty());
    pc.getInventory().addItem(std::move(item));
    EXPECT_FALSE(pc.getInventory().isEmpty());
}

TEST(PlayerCharacterTest, ArmorBonuses) 
{
    PlayerCharacter pc;
    auto armor = std::make_unique<Armor>("Titan Shield", 35, 80);
    
    pc.equipArmor(std::move(armor));
    pc.updateArmorBonuses();
    EXPECT_GT(pc.getStrengthBonus(), 0);
}