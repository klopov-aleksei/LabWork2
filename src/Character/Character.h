#ifndef CHARACTER_H
#define CHARACTER_H

#include "Equipment/Weapon.h"
#include "Equipment/Armor.h"
#include "Constants.h"

#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <iostream>

class Item;
class Skill;
class DamageCalculator;

class Character 
{
protected:
    std::string m_name;
    int m_strength{ 5 };
    int m_intelligence{ 5 };
    int m_health{ 100 };
    int m_maxHealth{ 100 };
    int m_agility{ 5 };
    int m_actionPoints{ Constants::initial_ap };
    int m_maxActionPoints{ Constants::initial_ap };
    int m_mana{ 50 };
    int m_maxMana{ 50 };
    bool m_isBlocking{ false };

    std::unique_ptr<Weapon> equippedWeapon;
    std::unique_ptr<Armor> equippedArmor;

public:
    Character(std::string_view name, int strength, int intelligence, int agility, int mana);
    Character(std::string_view name, int agility, int mana);
    Character() = default;

    virtual ~Character() = default;

    void setStats(int strength, int intelligence);
    void setBlocking(bool state);
    bool isBlocking() const;

    const std::string& getName() const;
    int getStrength() const;
    int getIntelligence() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getAgility() const;
    int getActionPoints() const;
    int getMana() const;
    bool isDead() const;

    void increaseHealth(int amount);
    void increaseMana(int amount);

    template<typename T>
    void modifyStat(T Character::* statPtr, T delta, const std::string& statName)
    {
        this->*statPtr += delta;
        std::cout << m_name << "'s " << statName << " changed by " << delta << ".\n";
    }

    void increaseMaxHealth(int amount) { modifyStat(&Character::m_maxHealth, amount, "max health"); }
    void increaseMaxMana(int amount) { modifyStat(&Character::m_maxMana, amount, "max mana"); }
    void increaseStrength(int amount) { modifyStat(&Character::m_strength, amount, "strength"); }
    void increaseIntelligence(int amount) { modifyStat(&Character::m_intelligence, amount, "intelligence"); }
    void increaseAgility(int amount) { modifyStat(&Character::m_agility, amount, "agility"); }
    void increaseActionPoints(int amount) { modifyStat(&Character::m_maxActionPoints, amount, "action capacity"); }

    void repairArmor(int durability);
    void repairWeapon(int durability);
    
    virtual void displayStatus() const = 0;

    void equipWeapon(std::unique_ptr<Weapon> weapon);
    void equipArmor(std::unique_ptr<Armor> armor);

    void takeDamage(DamageCalculator& dmgCalc);
    void takeDamage(int damage);
    void takeActionPoints(int cost);
    void resetActionPoints();
    void setActionPoints(int ap);
    void useMana(int cost);

    Weapon* getWeapon() const { return equippedWeapon.get(); }
    Armor* getArmor() const { return equippedArmor.get(); }
};

#endif