#include "Character/Character.h"
#include "Character/PlayerCharacter.h"
#include "Skills/Skill.h"
#include "Equipment/Item.h"
#include "Game/DamageCalculator.h"
#include "Constants.h"
#include "Random.h"

#include <iostream>
#include <iomanip>

Character::Character(std::string_view name, int strength,
                            int intelligence, int agility, int mana, int health, int actionPoints)
    : m_name{ name }
    , m_strength{ strength }
    , m_intelligence{ intelligence }
    , m_agility{ agility } 
    , m_mana{ mana }
    , m_maxMana{ mana }
    , m_health{ health }
    , m_maxHealth{ health }
    , m_actionPoints{ actionPoints }
    , m_maxActionPoints{ actionPoints }
{
}

Character::Character(std::string_view name, int agility, int mana)
    : m_name{ name }
    , m_agility{ agility }
    , m_mana{ mana }
    , m_maxMana{ mana }
{
}

void Character::setStats(int strength, int intelligence)
{
    m_strength = strength;
    m_intelligence = intelligence;
}

void Character::setBlocking(bool state)
{
    m_isBlocking = state;
}

bool Character::isBlocking() const
{
    return m_isBlocking;
}

void Character::incrementAttackCount() { ++m_attackCount; }
void Character::resetAttackCount() { m_attackCount = 0; }
void Character::resetActionPoints() 
{ 
    m_actionPoints = m_maxActionPoints; 
    resetAttackCount();
}
int Character::getAttackCount() const
{
    return m_attackCount;
}

const std::string& Character::getName() const { return m_name; }
int Character::getStrength() const { return m_strength; }
int Character::getIntelligence() const { return m_intelligence; }
int Character::getHealth() const { return m_health; }
int Character::getMaxHealth() const { return m_maxHealth; }
int Character::getAgility() const { return m_agility; }
int Character::getActionPoints() const { return m_actionPoints; }
int Character::getMana() const { return m_mana; }
bool Character::isDead() const { return m_health <= 0; }

void Character::increaseHealth(int amount)
{
    int newHealth = std::min(m_health + amount, m_maxHealth);
    std::cout << m_name << "'s health changed from " << m_health << " to " << newHealth << ".\n";
    m_health = newHealth;
}

void Character::increaseMana(int amount)
{
    int newMana = std::min(m_mana + amount, m_maxMana);
    std::cout << m_name << "'s mana changed from " << m_mana << " to " << newMana << ".\n";
    m_mana = newMana;
}

void Character::repairArmor(int durability) // better to implement as non-member functions.
{
    if (equippedArmor)
    {
        equippedArmor->repair(durability);
        std::cout << m_name << "'s armor has been repaired by " << durability << " durability.\n";
    }
    else 
    {
        std::cout << m_name << " has no armor to repair!\n";
    }
}

void Character::repairWeapon(int durability)
{
    if (equippedWeapon) 
    {
        equippedWeapon->repair(durability);
        std::cout << m_name << "'s weapon has been repaired by " << durability << " durability.\n";
    }
    else 
    {
        std::cout << m_name << " has no weapon to repair!\n";
    }
}

void Character::equipWeapon(std::unique_ptr<Weapon> weapon) 
{
    if (weapon) 
    {
        weapon->runCustomEffect(*this);
    }
    equippedWeapon = std::move(weapon);
}

void Character::equipArmor(std::unique_ptr<Armor> armor) 
{   
    if (armor) 
    {
        equippedArmor = std::move(armor);
        if (auto* pc = dynamic_cast<PlayerCharacter*>(this)) 
        {
            pc->updateArmorBonuses();
        }
        equippedArmor->runCustomEffect(*this);
    }
}

void Character::takeDamage(DamageCalculator& dmgCalc) 
{
    if (equippedArmor) 
    {
        equippedArmor->takeDamage(dmgCalc.m_armorDamage);
        std::cout << m_name << "'s armor condition: "
                  << std::fixed << std::setprecision(2)
                  << equippedArmor->getCondition() * 100 << "% ("
                  << equippedArmor->getCurrentDurability() << "/" 
                  << equippedArmor->getMaxDurability() << ")\n";
        if (equippedArmor->isBroken()) 
        {
            std::cout << m_name << "'s armor has broken and is unequipped!\n";
            equippedArmor.reset();
        }
    }

    m_health -= dmgCalc.m_finalDamage;
    m_health = std::max(0, m_health);

    std::cout << m_name << " takes " << dmgCalc.m_finalDamage << " damage.\n";
}

void Character::takeDamage(int damage)
{
    // Block doesn't affect damage.

    if (equippedArmor)
    {
        equippedArmor->takeDamage(damage);
        std::cout << m_name << "'s armor condition: " 
                  << equippedArmor->getCondition() * 100 << "% ("
                  << equippedArmor->getCurrentDurability() << "/" 
                  << equippedArmor->getMaxDurability() << ")\n";
        if (equippedArmor->getCurrentDurability() <= 0) 
        {
            std::cout << m_name << "'s armor has broken and is unequipped!\n";
            equippedArmor.reset();
        }
    }
    else
    {
        m_health -= damage;
        m_health = std::max(0, m_health);
        std::cout << m_name << " takes " << damage << " damage.\n";
    }
}

void Character::takeActionPoints(int cost) 
{
    m_actionPoints -= cost;
    if (m_actionPoints < 0) m_actionPoints = 0;
}
void Character::useMana(int cost) 
{
    m_mana -= cost;
    if (m_mana < 0) m_mana = 0;
}
