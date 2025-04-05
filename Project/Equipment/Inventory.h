#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <memory>

#include "Item.h"

class Character;

class Inventory 
{
    std::vector<std::unique_ptr<Item>> m_items;
    int inventorySize{ 5 };
    
public:
    int size() const;
    void newSize();
    void addItem(std::unique_ptr<Item> item);
    void removeItem(int index);
    void removeBrokenItems();

    void useItem(int index, Character& user, Character* enemy = nullptr);
    void display() const;
};

#endif