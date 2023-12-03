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

        int GetCapacity() { return this->capacity; }
        int numberOfItems; // stores the current number of items in the inventory

    private:
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