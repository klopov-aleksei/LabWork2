#ifndef ITEM_H
#define ITEM_H

#include "StatModifier.h"

#include <string>
#include <string_view>
#include <functional>
#include <iostream>

enum class Rarity
{
    common,
    uncommon,
    rare,
    epic
};

class Character;
class Investigate;

class Item 
{
protected:
    std::string m_name;
    Rarity m_rarity;
    std::vector<StatModifier> m_modifiers;

    std::function<void(Character&)> m_customEffect;
    bool m_effectApplied{ false };
    
public:
    Item(std::string_view name, Rarity rarity, const std::vector<StatModifier>& modifiers,
        std::function<void(Character&)> customEffect = nullptr);
    Item(std::string_view name, Rarity rarity, std::function<void(Character&)> customEffect = nullptr);
        
    virtual ~Item() = default;
    
    const std::string& getName() const { return m_name; }
    Rarity getRarity() const { return m_rarity; }
    const std::vector<StatModifier>& getModifiers() const { return m_modifiers; }

    std::string_view getRarityName() const;

    void setCustomEffect(std::function<void(Character&)> effect) { m_customEffect = std::move(effect); } 
    void runCustomEffect(Character& user);
    void use(Character& user, Character* enemy = nullptr);
};

#endif
