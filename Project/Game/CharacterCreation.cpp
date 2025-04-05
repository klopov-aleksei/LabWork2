#include "CharacterCreation.h"
#include "Constants.h"

#include <limits>
#include <vector>
#include <string_view>

std::unique_ptr<PlayerCharacter> CharacterCreation::createCharacter()
{
    std::string name{ ChooseName() };
    auto character{ ChooseClass(name) };
    CustomizeStats(*character);
    ChooseWeapon(*character);
    ChooseArmor(*character);
    ChooseSkills(*character);
    ChooseInventory(*character);

    return character;
}

std::string CharacterCreation::ChooseName() 
{
    std::string name;
    std::cout << "Enter your character's name: ";
    std::getline(std::cin, name);
    return name;
}

std::unique_ptr<PlayerCharacter> CharacterCreation::ChooseClass(std::string_view name) 
{
    std::cout << "Choose your class:\n";
    int choice{};
    while (true) 
    {
        std::cout << "1. Warrior\n2. Mage\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 1) return std::make_unique<Warrior>(name);
        if (choice == 2) return std::make_unique<Mage>(name);

        std::cout << "Invalid choice. Try again.\n";
    }
}

void CharacterCreation::CustomizeStats(PlayerCharacter& character)
{
    std::cout << "You have " << Constants::points_to_distribute 
              << " stat points to distribute.\n";
    int remainingPoints{ Constants::points_to_distribute };
    int strength{}, intelligence{};

    while (remainingPoints > 0)
    {
        std::cout << "Remaining points: " << remainingPoints << "\n";
        std::cout << "Enter points for Strength: ";
        std::cin >> strength;
        std::cout << "Enter points for Intelligence: ";
        std::cin >> intelligence;

        if (std::cin.fail() || strength + intelligence > 10 
            || strength < 0 || intelligence < 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please distribute exactly 10 points.\n";
            continue;
        }
        break;
    }
    
    character.setStats(strength, intelligence);
}

void CharacterCreation::ChooseWeapon(PlayerCharacter& character)
{
    int choice;
    while (true)
    {
        std::cout << "\nChoose your weapon:\n";
        std::cout << "1. Sword\n"; // (10 damage, 20 durability)
        std::cout << "2. Staff\n"; // (3 damage, 30 durability)
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 1)
        {
            character.equipWeapon(std::make_unique<Weapon>("Sword", 10, 20));
            break;
        }
        else if (choice == 2)
        {
            character.equipWeapon(std::make_unique<Weapon>("Staff", 3, 30));
            break;
        }
        else
        {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}

void CharacterCreation::ChooseArmor(PlayerCharacter& player) 
{
    std::cout << "\nChoose your armor:\n";
    std::cout << "1. Light Armor\n"; // (+5 agility, low defense)
    std::cout << "2. Medium Armor\n"; // (+3 agility, medium defense)
    std::cout << "3. Heavy Armor\n"; // (+1 agility, high defense)
    
    int choice;
    std::cin >> choice;
    
    std::unique_ptr<Armor> chosenArmor;
    
    switch (choice) 
    {
        case 1:
            chosenArmor = std::make_unique<Armor>("Light Armor", 5, 10);
            break;
        case 2:
            chosenArmor = std::make_unique<Armor>("Medium Armor", 3, 20);
            break;
        case 3:
            chosenArmor = std::make_unique<Armor>("Heavy Armor", 1, 30);
            break;
        default:
            std::cout << "Invalid choice, defaulting to Medium Armor.\n";
            chosenArmor = std::make_unique<Armor>("Medium Armor", 3, 20);
            break;
    }

    player.equipArmor(std::move(chosenArmor));
    std::cout << "Equipped " << player.getArmor()->getName() << "!\n";
}

void CharacterCreation::ChooseSkills(PlayerCharacter& player)
{
    std::cout << "\nChoose ONE additional skill:\n";
    std::cout << "1. Heal\n";
    std::cout << "2. Increase Inventory\n"; // (Hold 10 items instead of 5)
    std::cout << "3. Become a Monk\n"; // (Concentration restores more mana & stamina)
    std::cout << "4. EasyBlock\n"; // (Block costs less action points)
    if (dynamic_cast<Warrior*>(&player))
    {
        std::cout << "5. Learn Spellcasting\n";
    }

    int maxOption { dynamic_cast<Warrior*>(&player) ? 5 : 4 };
    int skillChoice;
    while (!(std::cin >> skillChoice) || skillChoice < 1 || skillChoice > maxOption)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Choose a valid skill option: ";
    }

    switch (skillChoice)
    {
    case 1:
        player.unlockHealing();
        std::cout << "You have learned 'Heal'!\n";
        break;
    case 2:
        player.getInventory().newSize();
        std::cout << "You can now hold 10 items instead of 5!\n";
        break;
    case 3:
        player.boostConcentration();
        std::cout << "Your concentration now restores more mana and stamina!\n";
        break;
    case 4:
        player.reduceBlockCost();
        std::cout << "Your Block skill now costs fewer action points!\n";
        break;
    case 5:
        // player.LearnSkill(std::make_unique<SpellCast>());
        player.enableSpellCast();
        std::cout << "You have learned 'Attack Spellcasting'!\n";
        break;
    }

    std::cout << "Skill selection complete!\n";
}

void CharacterCreation::ChooseInventory(PlayerCharacter& player)
{
    std::cout << "\nStarting inventory includes a basic healing potion.\n";
    std::vector<StatModifier> basicHealingModifiers
    {
        { Stat::health, 20, Target::self }
    };
    player.getInventory().addItem(std::make_unique<Item>(
        "Basic Healing Potion", 
        Rarity::common, 
        basicHealingModifiers));

    std::cout << "Choose one additional item:\n";
    std::cout << "1) Spell Scroll (Fireball)\n";
    std::cout << "2) Small Mana Potion\n";
    std::cout << "3) Repair Kit\n";
    std::cout << "4) Nothing\n";

    int choice;
    while (!(std::cin >> choice) || choice < 1 || choice > 4)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Choose a valid option: ";
    }
    
    switch (choice)
    {
    case 1:
    {
        std::vector<StatModifier> fireballModifiers
        {
            { Stat::damage, 25, Target::enemy }
        };
        player.getInventory().addItem(std::make_unique<Item>(
            "Fireball Scroll", 
            Rarity::uncommon, 
            fireballModifiers));
        std::cout << "You received a Spell Scroll (Fireball).\n";
        break;
    }
    case 2:
    {
        std::vector<StatModifier> manaPotionModifiers
        {
            { Stat::mana, 15, Target::self }
        };
        player.getInventory().addItem(std::make_unique<Item>(
            "Small Mana Potion", 
            Rarity::uncommon, 
            manaPotionModifiers));
        std::cout << "You received a Small Mana Potion.\n";
        break;
    }
    case 3:
    {
        std::vector<StatModifier> repairKitModifiers
        {
            { Stat::repair, 10, Target::armor },
            { Stat::repair, 10, Target::weapon }
        };
        player.getInventory().addItem(std::make_unique<Item>(
            "Repair Kit", 
            Rarity::uncommon, 
            repairKitModifiers));
        std::cout << "You received a Repair Kit.\n";
        break;
    }
    case 4:
        std::cout << "No additional item selected.\n";
        break;
    }
}
