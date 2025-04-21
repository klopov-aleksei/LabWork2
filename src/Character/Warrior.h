#ifndef WARRIOR_H
#define WARRIOR_H

#include "PlayerCharacter.h"

class Warrior : public PlayerCharacter 
{
private:
    bool m_blockSuccess{ false };
    bool m_damageBuff{ false };

public:
    Warrior(std::string_view name);

    void setBlockSuccess(bool success);
    bool isDamageBuffActive() const;
    void resetDamageBuff();

    void resetActionPoints() override;
};

#endif