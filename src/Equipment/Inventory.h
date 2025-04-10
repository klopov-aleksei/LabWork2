#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <memory>

class Item;
class Character;

class Inventory 
{
    std::vector<std::unique_ptr<Item>> m_items;
    int inventorySize{ 5 };
    
public:
    int getItemCount() const;
    bool isFull() const;
    void newSize();
    int getSize() const;

    const Item* operator[] (int index) const;

    void addItem(std::unique_ptr<Item> item);
    void removeItem(int index);
    void removeBrokenItems();

    void useItem(int index, Character& user, Character* enemy = nullptr);
    void display() const;
    bool isEmpty() const;
};

#endif