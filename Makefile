CXX = g++
CXXFLAGS = -std=c++23 -Wall -Werror -Wpedantic -O2 -Isrc
LDFLAGS = -lgtest -lgtest_main -lpthread

SRC = src/main.cpp \
      src/Character/Character.cpp \
      src/Character/PlayerCharacter.cpp \
      src/Character/Mage.cpp \
      src/Character/Warrior.cpp \
      src/Character/NPC.cpp \
      src/Character/EasyEnemy.cpp \
      src/Character/MediumEnemy.cpp \
      src/Character/HardEnemy.cpp \
      src/Equipment/Armor.cpp \
      src/Equipment/Equipment.cpp \
      src/Equipment/Inventory.cpp \
      src/Equipment/Item.cpp \
      src/Equipment/Weapon.cpp \
      src/Skills/Skill.cpp \
      src/Skills/Block.cpp \
      src/Skills/Concentrate.cpp \
      src/Skills/Heal.cpp \
      src/Skills/Investigate.cpp \
      src/Skills/MeleeAttack.cpp \
      src/Skills/SpellCast.cpp \
      src/Game/CharacterCreation.cpp \
      src/Game/CombatInterface.cpp \
      src/Game/CombatSystem.cpp \
      src/Game/Game.cpp \
      src/Game/computeStatBonus.cpp \
      src/Game/calculateDamage.cpp

TEST_SRC = tests/CharacterTest.cpp \
          tests/PlayerCharacterTest.cpp \
          tests/MageTest.cpp \
          tests/WarriorTest.cpp \
          tests/NPCTest.cpp \
          tests/EasyEnemyTest.cpp \
          tests/MediumEnemyTest.cpp \
          tests/HardEnemyTest.cpp \
          tests/ItemTest.cpp \
          tests/EquipmentTest.cpp \
          tests/ArmorTest.cpp \
          tests/WeaponTest.cpp \
          tests/InventoryTest.cpp \
          tests/HealTest.cpp \
          tests/ConcentrateTest.cpp \
          tests/InvestigateTest.cpp \
          tests/BlockTest.cpp \
          tests/MeleeAttackTest.cpp \
          tests/SpellCastTest.cpp \
          tests/CombatInterfaceTest.cpp \
          tests/CombatSystemTest.cpp \
          tests/DamageCalculatorTest.cpp \
          tests/computeStatBonusTest.cpp

OBJ = $(SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)
EXE = rpg_game
TEST_EXE = test_game

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test: $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE): $(TEST_OBJ) $(filter-out src/main.o, $(OBJ))
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXE) $(TEST_OBJ) $(TEST_EXE)

.PHONY: all test clean