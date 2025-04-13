#include "gtest/gtest.h"
#include "Skills/Investigate.h"
#include "Character/PlayerCharacter.h"
#include "Random.h"
#include "Constants.h"

TEST(InvestigateTest, ItemGeneration) {
    PlayerCharacter pc{ "Scout", 5, 50 }; // Agility=5, Mana=50
    Investigate investigate;
    pc.resetActionPoints();
    
    auto old_size = pc.getInventory().getItemCount();
    investigate.execute(pc);
    EXPECT_GT(pc.getInventory().getItemCount(), old_size);
    EXPECT_EQ(pc.getActionPoints(), 10 - Constants::invest_cost);
}

int findValidSeed() 
{
    int seed = 0;
    for (; seed < 10000; ++seed) 
    {
        std::mt19937 rng(seed);
        Random::mt = rng;
        if(Random::get(1,100) <= 3) 
            return seed;
    }
    return seed;
}

TEST(InvestigateTest, EpicItemGeneration) {
    PlayerCharacter pc("Scout", 5, 50);
    Investigate investigate;
    pc.resetActionPoints();

    // Force RNG for an epic item
    std::mt19937 forced_rng(findValidSeed());
    Random::mt = forced_rng;
    
    investigate.execute(pc);
    
    // Verify inventory contains epic item
    bool found_epic = false;
    for(int i = 1; i <= pc.getInventory().getItemCount(); ++i) {
        const Item* item = pc.getInventory()[i];
        if(item && item->getRarity() == Rarity::epic) {
            found_epic = true;
            break;
        }
    }
    
    EXPECT_TRUE(found_epic) << "No epic items found in inventory. Items:";
    for(int i = 1; i <= pc.getInventory().getItemCount(); ++i) {
        const Item* item = pc.getInventory()[i];
        if(item) {
            std::cout << " - " << item->getName() 
                     << " (Rarity: " << static_cast<int>(item->getRarity())
                     << ")\n";
        }
    }
}