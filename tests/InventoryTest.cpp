#include "gtest/gtest.h"
#include "Equipment/Inventory.h"
#include "Equipment/Item.h"
#include "Equipment/Weapon.h"

TEST(InventoryTest, AddAndRemoveItems) {
    Inventory inv;
    auto item = std::make_unique<Item>("Health Potion", Rarity::common);
    
    // Test adding
    inv.addItem(std::move(item));
    EXPECT_EQ(inv.getItemCount(), 1);
    EXPECT_FALSE(inv.isEmpty());
    
    // Test removing
    inv.removeItem(-1);
    EXPECT_TRUE(inv.isEmpty());
}

TEST(InventoryTest, CapacityEnforcement) {
    Inventory inv;
    
    // Default capacity is 5
    for(int i = 1; i <= 5; i++) {
        inv.addItem(std::make_unique<Item>("Item " + std::to_string(i), Rarity::common));
    }
    
    EXPECT_EQ(inv.getItemCount(), 5);
    EXPECT_TRUE(inv.isFull());
}

TEST(InventoryTest, BrokenItemRemoval) {
    Inventory inv;
    auto weapon = std::make_unique<Weapon>("FragileSword", 10, 5);
    
    // Break the weapon
    weapon->takeDamage(10);
    
    // Add and test removal
    inv.addItem(std::move(weapon));
    inv.removeBrokenItems();
    EXPECT_TRUE(inv.isEmpty());
}