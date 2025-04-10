CXX = g++
CXXFLAGS = -std=c++23 -Wall -Werror -Wpedantic -O2 -I.
LDFLAGS = 

SRC = main.cpp \
       Character/Character.cpp \
       Character/PlayerCharacter.cpp \
       Character/NPC.cpp \
       Character/MediumEnemy.cpp \
       Equipment/Armor.cpp \
       Equipment/Equipment.cpp \
       Equipment/Inventory.cpp \
       Equipment/Item.cpp \
       Equipment/Weapon.cpp \
       Skills/Skill.cpp \
       Skills/Block.cpp \
       Skills/Concentrate.cpp \
       Skills/Heal.cpp \
       Skills/Investigate.cpp \
       Skills/MeleeAttack.cpp \
       Skills/SpellCast.cpp \
       Game/CharacterCreation.cpp \
       Game/CombatInterface.cpp \
       Game/CombatSystem.cpp \
       Game/Game.cpp \
       Game/computeStatBonus.cpp \
       Game/calculateDamage.cpp

OBJ = $(SRC:.cpp=.o)
EXE = rpg_game

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(EXE)

