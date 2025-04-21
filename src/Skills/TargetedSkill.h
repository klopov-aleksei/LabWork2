#ifndef TARGETED_SKILL_H
#define TARGETED_SKILL_H

#include "Skill.h"

class TargetedSkill : public Skill 
{
private:
    int m_damage;

public:
    TargetedSkill(Type type, int cost, int damage) : Skill(type, cost), m_damage{ damage } { }
    int getDamage() { return m_damage; }
    virtual void execute(Character& user, Character& target) = 0;
};

#endif