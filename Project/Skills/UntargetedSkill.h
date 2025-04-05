#ifndef UN_TARGETED_SKILL_H
#define UN_TARGETED_SKILL_H

#include "Skill.h"

class UntargetedSkill : public Skill 
{
public:
    UntargetedSkill(Type type, int cost) : Skill(type, cost) { }
    virtual void execute(Character& user) = 0;
};

#endif