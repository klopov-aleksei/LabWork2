#include "gtest/gtest.h"
#include "Game/DamageCalculator.h"
#include "Character/PlayerCharacter.h"
#include "Equipment/Armor.h"
#include "Game/computeStatBonus.h"

TEST(DamageCalculatorTest, ArmorDamageAbsorption) {
    DamageCalculator dmgCalc;
    PlayerCharacter pc;
    pc.equipArmor(std::make_unique<Armor>("TestArmor", 20, 100));
    calculateDamage(dmgCalc, pc, 30, 0, 0);
    pc.takeDamage(dmgCalc);
    EXPECT_GT(pc.getArmor()->getCurrentDurability(), 0);
    EXPECT_LT(pc.getHealth(), 100);
}

TEST(DamageCalculatorTest, BlockReducesDamage) {
    PlayerCharacter pc;
    const int initialHealth = pc.getHealth();

    const int baseDamage = 50;
    DamageCalculator dmgCalc;

    pc.setBlocking(true);
    calculateDamage(dmgCalc, pc, baseDamage, 0, 0);
    pc.takeDamage(dmgCalc);

    const int damageTaken = initialHealth - pc.getHealth();
    EXPECT_LT(damageTaken, baseDamage) 
        << "Blocking should reduce incoming damage";
    
    if(pc.getArmor()) {
        EXPECT_LT(pc.getArmor()->getCurrentDurability(), 
                pc.getArmor()->getMaxDurability())
            << "Armor should absorb some damage";
    }
}