#ifndef SPELL_CAST_H
#define SPELL_CAST_H

#include "TargetedSkill.h"
#include "Character/Character.h"

class SpellCast : public TargetedSkill
{
private:
    int m_manaCost;

public:
    SpellCast(int manaCost=15, int damage=15);
    
    void execute(Character& user, Character& target) override;
    
    std::string_view getName() const override { return "Cast a spell"; }
};

#endif