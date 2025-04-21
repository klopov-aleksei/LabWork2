#include "gtest/gtest.h"
#include "Game/CombatInterface.h"
#include "Character/PlayerCharacter.h"
#include "Character/EasyEnemy.h"
#include "Game/CombatSystem.h"

class CombatInterfaceTest : public ::testing::Test {
protected:
    PlayerCharacter player;
    EasyEnemy enemy;
    CombatSystem combatSystem;
    CombatInterface combatInterface;

    CombatInterfaceTest() 
        : player("TestPlayer", 5, 50),
          combatSystem(player, enemy),
          combatInterface(player, combatSystem) {}
};

TEST_F(CombatInterfaceTest, AttackReducesAP) {
    player.resetActionPoints();
    combatInterface.performAttack();
    EXPECT_LT(player.getActionPoints(), 10);
}