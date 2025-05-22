#include "gtest/gtest.h"
#include "Game/CombatSystem.h"
#include "Character/PlayerCharacter.h"
#include "Character/EasyEnemy.h"
#include "Character/HardEnemy.h"

TEST(CombatSystemTest, TurnOrderByAgility) {
    PlayerCharacter player("Fast", 5, 50);
    EasyEnemy enemy;
    player.increaseAgility(10); // Higher than enemy's 5
    CombatSystem system(player, enemy);
    EXPECT_TRUE(system.getEnemy().getAgility() < player.getAgility());
}

TEST(CombatSystemTest, CombatEndsWhenPlayerDies) {
    PlayerCharacter player("Test", 5, 50);
    HardEnemy enemy;
    CombatSystem system(player, enemy);
    player.increaseHealth(-150);
    EXPECT_TRUE(system.isCombatOver());
}