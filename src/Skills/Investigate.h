#ifndef INVESTIGATE_H
#define INVESTIGATE_H

#include "UntargetedSkill.h"
#include "Equipment/Item.h"

#include <memory>
#include <vector>
#include <string>

class Character;
class Item;

class Investigate : public UntargetedSkill 
{
private:
    
    static std::unique_ptr<Item> createEpicItem();

    struct ModifierProfile 
    {
        int minMods;
        int maxMods;
        int negativeChance;
        int weakChance;
        int weakMin;
        int weakMax;
        int mediocreChance;
        int mediocreMin;
        int mediocreMax;
        int strongChance;
        int strongMin;
        int strongMax;
    };

    static const ModifierProfile commonProfile;
    static const ModifierProfile uncommonProfile;
    static const ModifierProfile rareProfile;

    static StatModifier generateModifier(const ModifierProfile& profile);

    static std::string getFriendlyNameForSingle(Stat stat, int bonus, Target target);
    static std::string generateMultiModifierName(Rarity overallRarity, const std::vector<StatModifier>& mods);

    static std::vector<StatModifier> combineModifiers(const std::vector<StatModifier>& mods);
    static bool isSumValid(Rarity rarity, int totalSum);

public:
    Investigate() : UntargetedSkill(Skill::Type::Utility, Constants::invest_cost) {}

    void execute(Character& user) override;
    static std::unique_ptr<Item> createGenericItem();

    std::string_view getName() const override { return "Investigate"; }
};

#endif