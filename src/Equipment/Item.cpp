#include "Item.h"
#include "Game/DamageCalculator.h"
#include "Character/Character.h"

Item::Item(std::string_view name, Rarity rarity, 
    const std::vector<StatModifier>& modifiers, 
    std::function<void(Character&)> customEffect)
    : m_name{ name }
    , m_rarity{ rarity }
    , m_modifiers{ modifiers }
    , m_customEffect{ std::move(customEffect) }
{
}
Item::Item(std::string_view name, Rarity rarity, std::function<void(Character&)> customEffect)
	: m_name{ name }
	, m_rarity{ rarity }
    , m_customEffect{ std::move(customEffect) }
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

void Item::runCustomEffect(Character& user) 
{
    if (m_customEffect) 
    {
        m_customEffect(user);
        m_customEffect = nullptr;
    }
}

void Item::use(Character& user, Character* enemy)
{
    const int cost{ 1 };
    std::cout << "Using " << m_name << " (" << getRarityName() << ")\n";
    runCustomEffect(user);

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
            {
                DamageCalculator dmgCalc;
                calculateDamage(dmgCalc, user, -mod.value, 0, 0); // attackCount&statBonus is zero for items
                enemy->takeDamage(dmgCalc);
                break;
            }
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
                    DamageCalculator dmgCalc;
                    calculateDamage(dmgCalc, *enemy, mod.value, 0, 0); // attackCount&statBonus is zero for items
                    enemy->takeDamage(dmgCalc);
                    break;
                }
                case Stat::health:
                {
                    enemy->increaseHealth(-mod.value);
                    break;
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
    user.takeActionPoints(cost);
}
