#include "Item.h"
#include "Game/DamageCalculator.h"
#include "Character/Character.h"

Item::Item(std::string_view name, Rarity rarity, 
    const std::vector<StatModifier>& modifiers, 
    std::function<void()> customEffect)
    : m_name{ name }
    , m_rarity{ rarity }
    , m_modifiers{ modifiers }
    , m_customEffect{ std::move(customEffect) }
{
}

Item::Item(std::string_view name, Rarity rarity)
	: m_name{ name }
	, m_rarity{ rarity }
{
}

std::string_view Item::getRarityName() const
{
    switch (m_rarity)
    {
    case Rarity::common: return "Common";
    case Rarity::uncommon: return "Uncommon";
    case Rarity::rare: return "Rare";
    case Rarity::epic: return "Epic";
    default: return "Unknown";
    }
}

void Item::use(Character& user, Character* enemy)
{
    if (m_customEffect)
    {
        m_customEffect();
        return;
    }

    for (const auto& mod : m_modifiers)
    {
        if ((mod.stat == Stat::health && mod.value < 0 && user.getHealth() + mod.value < 0) ||
            (mod.stat == Stat::mana && mod.value < 0 && user.getMana() + mod.value < 0))
        {
            std::cout << "Cannot use " << m_name << " because it would reduce your "
                      << ((mod.stat == Stat::health) ? "health" : "mana") << " below zero.\n";
            return;
        }
    }

    std::cout << "Using " << m_name << " (" << getRarityName() << ")\n";
       
    for (const auto& mod : m_modifiers)
    {
        if (mod.target == Target::self)
        {
            switch (mod.stat)
            {
            case Stat::health:
                user.increaseHealth(mod.value);
                break;
            case Stat::mana:
                user.increaseMana(mod.value);
                break;
            case Stat::maxHealth:
                user.increaseMaxHealth(mod.value);
                break;
            case Stat::maxMana:
                user.increaseMaxMana(mod.value);
                break;
            case Stat::strength:
                user.increaseStrength(mod.value);
                break;
            case Stat::intelligence:
                user.increaseIntelligence(mod.value);
                break;
            case Stat::agility:
                user.increaseAgility(mod.value);
                break;
            case Stat::actionPoints:
                user.increaseActionPoints(mod.value);
                break;
            case Stat::damage:
                user.takeDamage(mod.value);
                break;
            default: 
                break;
            }
        }
        else if (mod.target == Target::armor)
            user.repairArmor(mod.value);
        else if (mod.target == Target::weapon)
            user.repairWeapon(mod.value);
        else if (mod.target == Target::enemy)
        {
            if (enemy)
            {
                switch (mod.stat)
                {
                case Stat::damage:
                {
                    DamageCalculator dmgCalc;       // need to pass it to the function
                    dmgCalc.incrementAttackCount(); // so not to create a new object
                    enemy->takeDamage(mod.value);
                    break;
                }
                case Stat::health:
                {
                    enemy->increaseHealth(mod.value);
                }
                default:
                    std::cout << "Modifier targeting enemy not supported for this stat\n";
                    break;
                }
            }
            else
            {
                std::cout << "No enemy provided for enemy-targeted modifier.\n";
            }
        }
    }
    user.takeActionPoints(1);
}
