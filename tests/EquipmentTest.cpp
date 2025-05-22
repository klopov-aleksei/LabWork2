#include "gtest/gtest.h"
#include "Equipment/Equipment.h"

class TestEquipment : public Equipment {
public:
    TestEquipment() : Equipment("TestEquip", Rarity::common, 100) {}
    void use(Character& user, std::unique_ptr<Item> self) override {}
};

TEST(EquipmentTest, RepairMechanics) {
    TestEquipment equip;
    equip.takeDamage(60);
    equip.repair(30);
    
    EXPECT_EQ(equip.getCurrentDurability(), 70);
    EXPECT_FLOAT_EQ(equip.getCondition(), 0.7f);
}

TEST(EquipmentTest, BrokenStateDetection) {
    TestEquipment equip;
    equip.takeDamage(150);
    EXPECT_TRUE(equip.isBroken());
}