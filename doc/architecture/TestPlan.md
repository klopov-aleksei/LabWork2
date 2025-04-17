# Test Plan

## Unit Tests (Google Test)
- **Character Module**
  - CharacterTest.cpp
  - PlayerCharacterTest.cpp
  - MageTest.cpp
  - WarriorTest.cpp

- **NPC Module**
  - NPCTest.cpp
  - EasyEnemyTest.cpp
  - MediumEnemyTest.cpp
  - HardEnemyTest.cpp

- **Equipment Module**
  - ItemTest.cpp
  - EquipmentTest.cpp
  - ArmorTest.cpp
  - WeaponTest.cpp
  - InventoryTest.cpp

- **Skills Module**
  - HealTest.cpp
  - ConcentrateTest.cpp
  - InvestigateTest.cpp
  - BlockTest.cpp
  - MeleeAttackTest.cpp
  - SpellCastTest.cpp

- **Game & Utilities**
  - CombatInterfaceTest.cpp
  - CombatSystemTest.cpp
  - CharacterCreationTest.cpp
  - DamageCalculatorTest.cpp
  - computeStatBonusTest.cpp

## Integration Tests
- CharacterCreation → Game startup and class flow.
- Full CombatSystem + CombatInterface with scripted player inputs.
- Inventory interactions during combat (use, equip, dispose).

## End-to-End Tests
- Scripted scenarios across all difficulty levels: easy, medium, hard.
- Full playthrough with different class builds and skill/item combinations.

## Continuous Integration
- CI pipeline triggers on each push and PR (see .github/workflows/dev.yml).
- `make test` builds and runs all tests; required coverage ≥ 90%.