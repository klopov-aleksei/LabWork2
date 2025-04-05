#include "Investigate.h"
#include "Equipment/Armor.h"
#include "Equipment/Weapon.h"
#include "Equipment/Inventory.h"
#include "Character/PlayerCharacter.h"
#include "Random.h"

#include <algorithm>
#include <vector>
#include <sstream>

const Investigate::ModifierProfile Investigate::commonProfile = {
    /*weakChance*/ 80, /*mediocreChance*/ 20, /*strongChance*/ 0,
    /*negativeChance*/ 5, /*minMods*/ 1, /*maxMods*/ 2
};

const Investigate::ModifierProfile Investigate::uncommonProfile = {
    /*weakChance*/ 50, /*mediocreChance*/ 40, /*strongChance*/ 10,
    /*negativeChance*/ 10, /*minMods*/ 1, /*maxMods*/ 3
};

const Investigate::ModifierProfile Investigate::rareProfile = {
    /*weakChance*/ 20, /*mediocreChance*/ 50, /*strongChance*/ 30,
    /*negativeChance*/ 5, /*minMods*/ 2, /*maxMods*/ 3
};

const Investigate::ModifierProfile& Investigate::getProfileForRarity(Rarity rarity)
{
    switch(rarity)
    {
        case Rarity::rare:
            return rareProfile;
        case Rarity::uncommon:
            return uncommonProfile;
        default:
            return commonProfile;
    }
}

StatModifier Investigate::generateModifier(const ModifierProfile& profile)
{
    std::vector<Stat> possibleStats = { 
        Stat::health, Stat::mana, Stat::maxHealth, Stat::maxMana,
        Stat::strength, Stat::intelligence, Stat::agility, Stat::actionPoints,
        Stat::repair, Stat::damage 
    };
    int statIndex = Random::get(0, static_cast<int>(possibleStats.size()-1));
    Stat chosenStat{ possibleStats[statIndex] };
    
    // Decide if this modifier is negative.
    bool negative = (Random::get(1, 100) <= profile.negativeChance);
    
    // Decide bonus strength.
    int roll = Random::get(1, 100);
    int bonus = 0;
    if (roll <= profile.weakChance)
    {
        bonus = 1;
    }
    else if (roll <= profile.weakChance + profile.mediocreChance)
    {
        bonus = 2;
    }
    else
    {
        bonus = 3;
    }
    
    // If negative, make the bonus negative.
    if (negative)
        bonus = -bonus;
    
    // Decide target:
    // For "damage", a positive bonus means enemy damage, negative means self damage.
    // For any other stat, effects apply to self.
    Target target = Target::self;
    if (chosenStat == Stat::damage)
    {
        target = (bonus > 0) ? Target::enemy : Target::self;
    }
    
    return StatModifier{ chosenStat, bonus, target };
}

// Helper: generate a generic item using the weighted chance for rarity.
// The weighted chance for generic items (non–epic) is as follows:
// Common: 60%, Uncommon: 30%, Rare: 8%.
// (Epic items are handled separately.)
std::unique_ptr<Item> Investigate::createGenericItem()
{
    int roll = Random::get(1, 100);
    Rarity targetRarity;
    if (roll <= 8)       // 8% chance for rare
        targetRarity = Rarity::rare;
    else if (roll <= 8+30) // next 30% for uncommon
        targetRarity = Rarity::uncommon;
    else                  // remaining 60% for common
        targetRarity = Rarity::common;
    
    const ModifierProfile& profile = getProfileForRarity(targetRarity);
    int numMods = Random::get(profile.minMods, profile.maxMods);
    std::vector<StatModifier> mods;
    mods.reserve(numMods);
    for (int i = 0; i < numMods; ++i)
    {
        mods.push_back(generateModifier(profile));
    }
    
    // Safety check: if all modifiers are negative (i.e. only self–damage or other penalties),
    // then convert them to positive so that the item is at least somewhat helpful.
    bool hasPositive = false;
    for (const auto& mod : mods)
    {
        if (mod.value > 0)
        {
            hasPositive = true;
            break;
        }
    }
    if (!hasPositive)
    {
        for (auto& mod : mods)
        {
            mod.value = std::abs(mod.value);
        }
    }
    
    // Generate a name that incorporates the rarity and a summary of the modifiers.
    std::string baseName;
    switch(targetRarity)
    {
        case Rarity::rare: baseName = "Rare Relic"; break;
        case Rarity::uncommon: baseName = "Uncommon Talisman"; break;
        default: baseName = "Common Trinket"; break;
    }
    std::string itemName = generateItemName(baseName, targetRarity, mods);
    
    return std::make_unique<Item>(itemName, targetRarity, mods);
}

std::string Investigate::generateItemName(const std::string& baseName, Rarity rarity, const std::vector<StatModifier>& mods)
{
    std::stringstream ss;
    ss << baseName;
    ss << " {";
    for (size_t i = 0; i < mods.size(); ++i)
    {
        // Here we simply output the stat (as an int), the bonus and the target.
        ss << static_cast<int>(mods[i].stat) << ":" << mods[i].value;
        if (i < mods.size()-1)
            ss << ", ";
    }
    ss << "}";
    return ss.str();
}

std::unique_ptr<Item> Investigate::createEpicItem()
{
    int roll = Random::get(0, 3);
    switch(roll)
    {
        case 0:
            return std::make_unique<Weapon>("Excalibur", 50, 100);
        case 1:
            return std::make_unique<Weapon>("Aegis Blade", 48, 95);
        case 2:
            return std::make_unique<Armor>("Dragon Scale Armor", 40, 120);
        default:
            return std::make_unique<Armor>("Titan Shield", 38, 110);
    }
}

void Investigate::execute(Character& user)
{
    auto& player = dynamic_cast<PlayerCharacter&>(user); // not sure about it
    int roll = Random::get(1, 100);
    std::unique_ptr<Item> item;
    if (roll <= 2)
    {
        // Epic item.
        item = createEpicItem();
    }
    else
    {
        // Generic item.
        item = createGenericItem();
    }

    std::string foundName{ item->getName() };
    std::string_view foundRarity{ item->getRarityName() };

    player.getInventory().addItem(std::move(item));

    std::cout << "Investigated and found: " << foundName << " (" << foundRarity << ")\n";
}