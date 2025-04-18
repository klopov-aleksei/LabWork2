#include "Concentrate.h"
#include "Character/PlayerCharacter.h"

void Concentrate::execute(Character& user)
{
    int cost{ getCost() };
    int manaRestore{ Constants::concentrationManaRestore }; 
    if (auto* pc = dynamic_cast<PlayerCharacter*>(&user)) 
    { 
        if (pc->hasMonkTraining())
        { 
            manaRestore *= 2;
            cost -= 1;
        }
    } 

    if (user.getActionPoints() < cost) 
    {
        std::cout << "Not enough action points to execute " << getName() << ".\n";
        return;
    }
    std::cout << user.getName() << " concentrates, restoring " << manaRestore << " mana and boosting next turn's AP.\n"; 
    user.increaseMana(manaRestore);
    user.increaseActionPoints(1);
    user.takeActionPoints(cost);
}