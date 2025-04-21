#include "Inventory.h"
#include "Item.h"
#include "Character/Character.h"
#include "Equipment/Weapon.h"
#include "Equipment/Armor.h" 
#include <iostream>
#include <algorithm>

int Inventory::getItemCount() const { return static_cast<int>(m_items.size()); }
bool Inventory::isFull() const { return m_items.size() >= static_cast<size_t>(inventorySize); }
void Inventory::newSize() { inventorySize=10; }
int Inventory::getSize() const { return inventorySize; }

const Item* Inventory::operator[] (int index) const
{
    if (index < 1 || index > static_cast<int>(m_items.size())) 
        return nullptr;
    return m_items[index-1].get();
}

void Inventory::addItem(std::unique_ptr<Item> item) 
{
    m_items.emplace_back(std::move(item));
}

void Inventory::removeBrokenItems() 
{
    m_items.erase(
        std::remove_if(m_items.begin(), m_items.end(),
            [](const std::unique_ptr<Item>& item)
            {
                if (auto* eq = dynamic_cast<Equipment*>(item.get())) 
                {
                    return eq->isBroken();
                }
                return false;
            }),
        m_items.end());
}

void Inventory::removeItem(int index) 
{
    auto it = m_items.begin() + ((-index) - 1);
    std::string disposedName = (*it)->getName();
    m_items.erase(it);
    std::cout << disposedName << " disposed.\n";
}

void Inventory::useItem(int index, Character& user, Character* enemy)
{
    if (index < 1 || index > static_cast<int>(m_items.size())) 
    {
        std::cout << "Invalid item index!\n";
        return;
    }

    Item* itemPtr = m_items[index-1].get();
    if (!itemPtr->canUse(user)) 
    {
        std::cout << "Cannot use " << itemPtr->getName() << " as it would reduce your stat below zero.\n";
        return;
    }
    
    auto item = std::move(m_items[index-1]);
    m_items.erase(m_items.begin() + (index-1));

    if (dynamic_cast<Weapon*>(item.get()))
    {
        user.equipWeapon(std::unique_ptr<Weapon>(static_cast<Weapon*>(item.release())));
        std::cout << "Equipped " << user.getWeapon()->getName() << ".\n";
        user.takeActionPoints(1);
    }
    else if (dynamic_cast<Armor*>(item.get()))
    {
        user.equipArmor(std::unique_ptr<Armor>(static_cast<Armor*>(item.release())));
        std::cout << "Equipped " << user.getArmor()->getName() << ".\n";
        user.takeActionPoints(1);
    }
    else
    {
        item->use(user, enemy);
    }
}

void Inventory::display() const 
{
    if (isEmpty()) 
    {
        std::cout << "\nInventory is empty!\n";
        return;
    }
    std::cout << "\n=== Inventory ===\n";
    for(size_t i = 0; i < m_items.size(); ++i) {
        std::cout << i+1 << ". " << m_items[i]->getName();
        
        if(auto armor = dynamic_cast<Armor*>(m_items[i].get())) {
            std::cout << " (Armor) - " << armor->getCurrentDurability() 
                      << "/" << armor->getMaxDurability();
        }
        else if(auto weapon = dynamic_cast<Weapon*>(m_items[i].get())) {
            std::cout << " (Weapon) - " << weapon->getCurrentDurability()
                      << "/" << weapon->getMaxDurability();
        }
        
        std::cout << "\n";
    }
    std::cout << "=================\n";
}

bool Inventory::isEmpty() const
{
    if (m_items.empty()) 
    {
        return true;
    }
    return false;
}