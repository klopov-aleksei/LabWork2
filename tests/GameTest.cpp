#include "gtest/gtest.h"
#include "Game/Game.h"
#include "Character/HardEnemy.h"
#include "Character/MediumEnemy.h"
#include "Character/EasyEnemy.h"
#include <sstream>
#include <iostream>

class GameTest : public ::testing::Test {
protected:
    void redirectInput(const std::string& input) {
        old_cin = std::cin.rdbuf();
        std::cin.rdbuf(input_buffer.rdbuf());
        input_buffer.str(input);
    }

    void restoreInput() {
        std::cin.rdbuf(old_cin);
    }

    std::streambuf* old_cin;
    std::stringstream input_buffer;
};

TEST_F(GameTest, GameInitializationAndBasicCombatFlow) {
    redirectInput("3\n"); // Simulate choosing "3" for difficulty
    Game game;
    
    EXPECT_NO_THROW({
        game.start(); // Should create HardEnemy based on difficulty 3
    });
    
    // Test combat initialization with kept-alive enemies
    {
        HardEnemy hardEnemy;
        EXPECT_NO_THROW(game.startCombat(hardEnemy));
    }
    {
        MediumEnemy mediumEnemy;
        EXPECT_NO_THROW(game.startCombat(mediumEnemy));
    }
    {
        EasyEnemy easyEnemy;
        EXPECT_NO_THROW(game.startCombat(easyEnemy));
    }
    
    restoreInput();
}

TEST_F(GameTest, FullGameLifecycle) {
    redirectInput("2\n"); // Choose medium difficulty
    Game game;
    
    EXPECT_NO_THROW({
        game.start(); // Should create MediumEnemy
        // Let game manage its own lifecycle
    });
    
    restoreInput();
}