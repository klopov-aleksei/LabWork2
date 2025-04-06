#include "Investigate.h"
#include "Equipment/Armor.h"
#include "Equipment/Weapon.h"
#include "Equipment/Inventory.h"
#include "Character/PlayerCharacter.h"
#include "Random.h"

#include <algorithm>
#include <numeric>
#include <sstream>

const Investigate::ModifierProfile Investigate::commonProfile{ 
    /*minMods=*/1, /*maxMods=*/2, /*negativeChance=*/5,
    /*weakChance=*/100, /*weakMin=*/5, /*weakMax=*/10,
    /*mediocreChance=*/0, /*mediocreMin=*/10, /*mediocreMax=*/20,
    /*strongChance=*/0, /*strongMin=*/30, /*strongMax=*/40
};

const Investigate::ModifierProfile Investigate::uncommonProfile{ 
    /*minMods=*/1, /*maxMods=*/3, /*negativeChance=*/10,
    /*weakChance=*/70, /*weakMin=*/5, /*weakMax=*/10,
    /*mediocreChance=*/30, /*mediocreMin=*/10, /*mediocreMax=*/20,
    /*strongChance=*/0, /*strongMin=*/30, /*strongMax=*/40
};

const Investigate::ModifierProfile Investigate::rareProfile{ 
    /*minMods=*/1, /*maxMods=*/2, /*negativeChance=*/0,
    /*weakChance=*/20, /*weakMin=*/5, /*weakMax=*/10,
    /*mediocreChance=*/60, /*mediocreMin=*/10, /*mediocreMax=*/20,
    /*strongChance=*/40, /*strongMin=*/30, /*strongMax=*/40
};

StatModifier Investigate::generateModifier(const ModifierProfile& profile)
{
    std::vector<Stat> possibleStats = { 
        Stat::health, Stat::mana, Stat::maxHealth, Stat::maxMana,
        Stat::strength, Stat::intelligence, Stat::agility, Stat::actionPoints,
        Stat::repair, Stat::damage 
    };
    int statIndex = Random::get(0, static_cast<int>(possibleStats.size()-1));
    Stat chosenStat{ possibleStats[statIndex] };
    
    int tierRoll = Random::get(1, 100);
    int bonus = 0;
    if (tierRoll <= profile.weakChance)
        bonus = Random::get(profile.weakMin, profile.weakMax);
    else if (tierRoll <= profile.weakChance + profile.mediocreChance)
        bonus = Random::get(profile.mediocreMin, profile.mediocreMax);
    else
        bonus = Random::get(profile.strongMin, profile.strongMax);

    bool negative = (Random::get(1, 100) <= profile.negativeChance);
    if (negative)
    {
        bonus = -bonus;
        bonus = std::max(bonus, -profile.weakMax);
    }
    
    Target target = Target::self;
    if (chosenStat == Stat::damage)
    {
        target = (bonus > 0) ? Target::enemy : Target::self;
    }
    // For repair, choose randomly between armor and weapon.
    else if (chosenStat == Stat::repair)
    {
        target = (Random::get(0,1) == 0) ? Target::armor : Target::weapon;
    }
    // For other stats, effect applies to self.
    
    return StatModifier{ chosenStat, bonus, target };
}

std::string Investigate::getFriendlyNameForSingle(Stat stat, int bonus, Target target)
{
    if (stat == Stat::damage)
    {
        if(target == Target::enemy)
        {
            if(bonus >= 30) return "Lightning Bolt";
            else if(bonus > 10) return "Fireball";
            else return "Magic Scroll";
        }
        else
            return "Backfire";
    }

    if (bonus <= 0)
        return "Cursed Food";

    switch(stat)
    {
        case Stat::health:
            if (bonus >= 30) return "Health Elixir";
            else if (bonus > 10) return "Health Potion";
            else return "Food";
        case Stat::mana:
            if (bonus >= 30) return "Mana Elixir";
            else if (bonus > 10) return "Mana Tonic";
            else return "Mana Potion";
        case Stat::maxHealth:
            if (bonus >= 30) return "Miracle Salve";
            else if (bonus > 10) return "Advanced Bandage";
            else return "Bandage";
        case Stat::maxMana:
            if (bonus >= 30) return "Great Mystic Tonic";
            else if (bonus > 10) return "Mystic Tonic";
            else return "Mystic Herb";
        case Stat::strength:
            if (bonus >= 3) return "Power Drink";
            else if (bonus > 1) return "Protein Shake";
            else return "Dumbbell";
        case Stat::intelligence:
            if (bonus >= 3) return "Sage Elixir";
            else if (bonus > 1) return "Mind Tonic";
            else return "Herb";
        case Stat::agility:
            if (bonus >= 3) return "Windrunner Boots";
            else if (bonus > 1) return "Swift Boots";
            else return "Light Boots";
        case Stat::actionPoints:
            if (bonus >= 3) return "Legendary Amulet";
            else if (bonus > 1) return "Strong Amulet";
            else return "Amulet";
        case Stat::repair:
            // Here the effect is for equipment repair.
            if (bonus >= 30) return "Master Repair Kit";
            else if (bonus > 10) return "Toolbox";
            else return "Repair Kit";
        default:
            return "Mysterious Item";
    }
}

std::string Investigate::generateMultiModifierName(Rarity overallRarity, const std::vector<StatModifier>& mods)
{
    std::string baseName;
    switch(overallRarity)
    {
        case Rarity::rare: baseName = "Relic"; break;
        case Rarity::uncommon: baseName = "Talisman"; break;
        default: baseName = "Trinket"; break;
    }
    
    std::stringstream ss;
    ss << baseName << " (";
    for(size_t i = 0; i < mods.size(); ++i)
    {
        // Use a short label for the stat.
        std::string statLabel;
        switch (mods[i].stat)
        {
            case Stat::health: statLabel = "Health"; break;
            case Stat::mana: statLabel = "Mana"; break;
            case Stat::maxHealth: statLabel = "MaxHealth"; break;
            case Stat::maxMana: statLabel = "MaxMana"; break;
            case Stat::strength: statLabel = "Strength"; break;
            case Stat::intelligence: statLabel = "Intell"; break;
            case Stat::agility: statLabel = "Agility"; break;
            case Stat::actionPoints: statLabel = "AP"; break;
            case Stat::repair: statLabel = "Repair"; break;
            case Stat::damage: statLabel = "Damage"; break;
            default: statLabel = "Mystery"; break;
        }
        ss << statLabel << ":" << mods[i].value;
        if(i < mods.size()-1)
            ss << ", ";
    }
    ss << ")";
    return ss.str();
}

std::vector<StatModifier> Investigate::combineModifiers(const std::vector<StatModifier>& mods)
{
    std::vector<StatModifier> combined;
    for (const auto& mod : mods)
    {
        auto it = std::find_if(combined.begin(), combined.end(),
            [&mod](const StatModifier& m)
            {
                return (m.stat == mod.stat && m.target == mod.target);
            });
        if (it != combined.end())
        {
            it->value += mod.value;
        }
        else
        {
            combined.push_back(mod);
        }
    }
    return combined;
}

bool Investigate::isSumValid(Rarity rarity, int totalSum)
{
    switch (rarity) 
    {
        case Rarity::common:   return (totalSum >= 5  && totalSum <= 10);
        case Rarity::uncommon: return (totalSum >= 10 && totalSum <= 20);
        case Rarity::rare:    return (totalSum >= 30 && totalSum <= 40);
        default: return true;
    }
}

std::unique_ptr<Item> Investigate::createGenericItem()
{
    int roll = Random::get(1, 100);
    Rarity rarity;
    const ModifierProfile* profile = nullptr;
    if(roll <= 60)
    {
        rarity = Rarity::common;
        profile = &commonProfile;
    }
    else if(roll <= 90)
    {
        rarity = Rarity::uncommon;
        profile = &uncommonProfile;
    }
    else
    {
        rarity = Rarity::rare;
        profile = &rareProfile;
    }

    int totalSum;
    std::vector<StatModifier> mods;
    int numMods = Random::get(profile->minMods, profile->maxMods);
    mods.reserve(numMods);
    do 
    {
        mods.clear();
        for (int i{ 0 }; i < numMods; ++i) 
        {
            mods.emplace_back(generateModifier(*profile));
        }
        totalSum = std::accumulate(mods.begin(), mods.end(), 0, 
            [](int sum, const StatModifier& mod) { return sum + mod.value; });
    } while (!isSumValid(rarity, totalSum));
    mods = combineModifiers(mods);

    for (auto& mod : mods) 
    {
        if (mod.stat == Stat::agility || 
            mod.stat == Stat::actionPoints || 
            mod.stat == Stat::intelligence || 
            mod.stat == Stat::strength) 
        {
            int sign = (mod.value < 0) ? -1 : 1;
            int absValue = std::abs(mod.value);
            mod.value = sign * ((absValue + 5) / 10); // Scale down
        }
    }

    std::string itemName;
    if(mods.size() == 1)
        itemName = getFriendlyNameForSingle(mods[0].stat, mods[0].value, mods[0].target);
    else
        itemName = generateMultiModifierName(rarity, mods);
    
    return std::make_unique<Item>(itemName, rarity, mods);
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
    player.takeActionPoints(getCost());

    std::cout << "Investigated and found: " << foundName << " (" << foundRarity << ")\n";
}