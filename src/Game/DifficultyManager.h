#pragma once

#include "Character/NPC.h"

enum class Difficulty 
{ 
    Easy, 
    Medium, 
    Hard 
};

class DifficultyManager {
public:
    static std::unique_ptr<NPC> CreateEnemy(Difficulty level) {
        switch(level) 
        {
            case Difficulty::Easy:
                return std::make_unique<EasyEnemy>();
            case Difficulty::Medium:
                return std::make_unique<MediumEnemy>();
            case Difficulty::Hard:
                return std::make_unique<HardEnemy>();
        }
        return nullptr;
    }
};