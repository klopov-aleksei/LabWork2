#include "gtest/gtest.h"
#include "Character/HardEnemy.h"
#include "Character/Warrior.h"
#include "Equipment/Armor.h"

TEST(HardEnemyTest, BlocksWhenArmorLowAndPlayerStrong) {
    HardEnemy enemy;
    Warrior player("TestPlayer");

    // Activate player's damage buff
    player.setBlockSuccess(true);
    player.resetActionPoints();

    auto armor = std::make_unique<Armor>("CrackedArmor", 10, 50);
    armor->takeDamage(95); // <25% Durability
    enemy.equipArmor(std::move(armor));
    enemy.takeDamage(0); // to unequip broken armor

    enemy.increaseHealth(-250); // <25% Health

    // Set enemy's AP to block cost (5)
    enemy.resetActionPoints();
    enemy.takeActionPoints(4);

    enemy.performTurn(player);
    EXPECT_TRUE(enemy.isBlocking());
}