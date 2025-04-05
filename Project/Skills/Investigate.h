#ifndef INVESTIGATE_H
#define INVESTIGATE_H

#include "UntargetedSkill.h"
#include "Equipment/Item.h"

#include <memory>
#include <vector>
#include <functional>
#include <string>

class Character;

class Investigate : public UntargetedSkill 
{
private:
    
    static std::unique_ptr<Item> createEpicItem();
    static std::unique_ptr<Item> createGenericItem();
    // Helper: advanced generic item generator (for non–epic items).
    static std::unique_ptr<Item> createAdvancedGenericItem(const std::string& baseName, Rarity rarity);

    struct ModifierProfile 
    {
        // Probabilities (in percentages) for bonus strength.
        int weakChance;
        int mediocreChance;
        int strongChance;
        // Chance (in percentage) that the bonus is negative.
        int negativeChance;
        // Minimum and maximum number of modifiers.
        int minMods;
        int maxMods;
    };

    static const ModifierProfile commonProfile;
    static const ModifierProfile uncommonProfile;
    static const ModifierProfile rareProfile;

     // Helper to choose a profile based on rarity.
    static const ModifierProfile& getProfileForRarity(Rarity rarity);

    // Helper: generates a random modifier according to the profile.
    static StatModifier generateModifier(const ModifierProfile& profile);
    
    // Helper: generate a name for the item based on its modifiers.
    static std::string generateItemName(const std::string& baseName, Rarity rarity, const std::vector<StatModifier>& mods);

public:
    Investigate() : UntargetedSkill(Skill::Type::Utility, 1) {}

    void execute(Character& user) override;

    std::string_view getName() const override { return "Investigate"; }
};

#endif