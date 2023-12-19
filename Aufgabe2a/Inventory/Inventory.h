#pragma once

#include "../Exceptions/InventoryFull.h"
#include "../Exceptions/OutOfRange.h"
#include "../Exceptions/EquipmentError.h"
#include "../Exceptions/SlotIsEmpty.h"
#include "../Exceptions/UnequipError.h"

namespace Inventory
{

    template<typename T, int size>
    class Inventory
    {
    public:
        Inventory();

        T itemContainer[size] {};

        const static int equipmentSlots = 3; // number of special equipment slots
        T equipmentContainer[equipmentSlots] {};

        void AddItem(T item);
        T& GetItem(int slot);

        void EquipItem(T item);
        void UnequipItem(int slot);

    private:
        int capacity; // number of normal items you can store in the inventory
        int numberOfItems; // stores the current number of items in the inventory
    };

}

