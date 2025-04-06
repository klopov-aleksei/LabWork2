#include "Concentrate.h"

void Concentrate::execute(Character& user)
{
	std::cout << user.getName() << " concentrates, restoring mana and boosting next turn's AP.\n";
    user.increaseMana(Constants::concentrationManaRestore);
    user.increaseActionPoints(1);
    user.takeActionPoints(getCost());
}