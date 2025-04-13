#include "gtest/gtest.h"
#include "Character/EasyEnemy.h"
#include "Character/PlayerCharacter.h"
#include "Equipment/Weapon.h"

TEST(EasyEnemyTest, EquipsBackupWeaponWhenCurrentBreaks) {
    EasyEnemy enemy;
    PlayerCharacter player("TestPlayer", 5, 50);

    auto brokenWeapon = std::make_unique<Weapon>("Spear", 10, 0);
    brokenWeapon->takeDamage(10);
    enemy.equipWeapon(std::move(brokenWeapon));

    enemy.performTurn(player);
    
    ASSERT_NE(enemy.getWeapon(), nullptr);
    EXPECT_EQ(enemy.getWeapon()->getName(), "Gae Bolg");
}