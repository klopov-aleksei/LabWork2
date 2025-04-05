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

class Item 
{
protected:
    std::string m_name;
    Rarity m_rarity;
    std::vector<StatModifier> m_modifiers;

    // Optional
    std::function<void()> m_customEffect;
    
public:
    Item(std::string_view name, Rarity rarity, const std::vector<StatModifier>& modifiers,
        std::function<void()> customEffect = nullptr);

    Item(std::string_view name, Rarity rarity);
        
    virtual ~Item() = default;
    
    const std::string& getName() const { return m_name; }
    Rarity getRarity() const { return m_rarity; }

    std::string_view getRarityName() const;

    void use(Character& user, Character* enemy = nullptr);
};

#endif
