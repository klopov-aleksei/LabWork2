#ifndef BLOCK_H
#define BLOCK_H

#include "UntargetedSkill.h"
#include "Character/Character.h"
#include "Constants.h"

#include <string_view>
#include <iostream>

class Block : public UntargetedSkill 
{
public:
    Block() : UntargetedSkill(Skill::Type::Defense, Constants::block_cost) {}
    
    void execute(Character& user) override;
    
    std::string_view getName() const override { return "Block"; }
};

#endif