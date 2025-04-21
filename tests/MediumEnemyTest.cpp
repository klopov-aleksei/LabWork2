#include "gtest/gtest.h"
#include "Character/MediumEnemy.h"
#include "Character/PlayerCharacter.h"
#include "Equipment/Item.h"

class TestMediumEnemy : public MediumEnemy {
public:
    TestMediumEnemy() : MediumEnemy("TestEnemy", 6, 6, 7, 50, 300, 8) {}
    
    void addItemToInventory(std::unique_ptr<Item> item) {
        m_inventory.addItem(std::move(item));
    }

    void setTurnsSinceUltra(int turns) {
        m_turnsSinceUltra = turns;
    }
};

TEST(MediumEnemyTest, UsesHighPriorityItemFromInventory) {
    TestMediumEnemy enemy;
    PlayerCharacter player("TestPlayer", 5, 50);

    // Add items through exposed method
    enemy.addItemToInventory(std::make_unique<Item>(
        "Strength Potion", Rarity::common, 
        std::vector<StatModifier>{{Stat::strength, 10, Target::self}}
    ));
    enemy.addItemToInventory(std::make_unique<Item>(
        "Weak Potion", Rarity::common, 
        std::vector<StatModifier>{{Stat::health, 5, Target::self}}
    ));

    enemy.performTurn(player);
    EXPECT_GT(enemy.getStrength(), 6);
}

TEST(MediumEnemyTest, PerformsUltraAttackAfterThreshold) {
    TestMediumEnemy enemy;
    PlayerCharacter player("TestPlayer", 5, 50);

    // Use exposed method to set protected member
    player.increaseHealth(-60);
    enemy.setTurnsSinceUltra(3);

    int initialHealth = player.getHealth();
    enemy.performTurn(player);
    EXPECT_LT(player.getHealth(), initialHealth);
}