#pragma once

#include "../Exceptions/InventoryFull.h"
#include "../Exceptions/OutOfRange.h"
#include "../Exceptions/EquipmentError.h"
#include "../Items/BaseItem.h"

namespace Inventory
{

    template<typename T, int size>
    class Inventory
    {
    public:
        Inventory();

    // Normal inventory
        T itemContainer[size] {};

        void AddItem(T item);
        T& GetItem(int slot);
        T RemoveItem(int slot);
        void ResetInventory();

        int GetCapacity() { return this->capacity; }
        int GetCurrentNumberOfItems() { return this->numberOfItems; }
        int GetFirstEmptySlot();

        // Sort algorithms, using bubblesort
        void SortForWeight();
        void SortForName();
        void SortForCost();

    private:
        int numberOfItems; // stores the current number of items in the inventory
        int capacity; // number of normal items you can store in the inventory

    // Equipment slots
    private:
        const static int equipmentSlots = 3; // number of special equipment slots

    public:
        T equipmentContainer[equipmentSlots] {};

        void EquipItem(T item);
        void UnequipItem(int slot);

        int GetEquipmentSlots() { return equipmentSlots; }

    };

}