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
                return std::make_unique<EasyGoblin>();
            case Difficulty::Medium:
                return std::make_unique<MediumWarlock>();
            case Difficulty::Hard:
                return std::make_unique<HardDragon>();
        }
        return nullptr;
    }
};