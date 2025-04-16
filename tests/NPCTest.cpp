#include "gtest/gtest.h"
#include "Character/NPC.h"
#include "Character/PlayerCharacter.h"

class TestNPC : public NPC {
public:
    TestNPC() : NPC("TestNPC", 5, 5, 5, 50, 100, 10) {}
    void performTurn(PlayerCharacter& player) override {}
    void equipBackup() override {}

    void testPerformHeal() { performHeal(); }
    void testPerformSpellAttack(PlayerCharacter& player) { performSpellAttack(player); }
};

TEST(NPCTest, HealsWhenHealthLow) {
    TestNPC npc;
    PlayerCharacter player("TestPlayer", 5, 50);

    npc.increaseHealth(-60);
    npc.resetActionPoints(); 

    npc.testPerformHeal();
    EXPECT_GT(npc.getHealth(), 40); // Health should increase
}

TEST(NPCTest, SpellCastUsesMana) {
    TestNPC npc;
    PlayerCharacter player("TestPlayer", 5, 50);

    npc.resetActionPoints();
    npc.testPerformSpellAttack(player);
    EXPECT_LE(npc.getMana(), 30); // 50 base mana - 20 used
}