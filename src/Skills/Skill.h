#ifndef SKILL_H
#define SKILL_H

#include <string>

#include "Character/Character.h"

class Skill 
{
public:
    enum Type 
    {
        Damage,
        Heal,
        Defense,
        Utility
    };

protected:
    Type m_type;
    int m_cost;
    
public:
    Skill(Type type, int cost=0);

    virtual ~Skill() = default;

    int getCost() const{ return m_cost; }
    virtual std::string_view getName() const = 0;
};

#endif