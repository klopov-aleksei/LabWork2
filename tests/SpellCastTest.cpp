#include "gtest/gtest.h"
#include "Skills/SpellCast.h"
#include "Character/Mage.h"
#include "Equipment/Weapon.h"

class TestTarget : public Character {
public:
    TestTarget() : Character("TestTarget", 5, 5, 5, 50, 100, 10) {}
    void displayStatus() const override {}
};

TEST(SpellCastTest, ManaConsumption) {
    Mage mage("Merlin");
    TestTarget target;
    SpellCast spell;
    
    spell.execute(mage, target);
    EXPECT_EQ(mage.getMana(), 50 - 15);
}

TEST(SpellCastTest, StaffBonus) {
    Mage mage("Merlin");
    TestTarget target;
    auto staff = std::make_unique<Weapon>("Staff", 5, 30);
    mage.equipWeapon(std::move(staff));
    
    SpellCast spell;
    spell.execute(mage, target);
    EXPECT_EQ(mage.getMana(), 50 - 10);
}