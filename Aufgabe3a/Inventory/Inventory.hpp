#include "Inventory.h"

namespace Inventory
{

    template<typename T, int size>
    Inventory<T, size>::Inventory()
    {
        numberOfItems = 0;
        capacity = size;
    }

    template<typename T, int size>
    void Inventory<T, size>::AddItem(T item)
    {
        if (numberOfItems < capacity)
        {
            int emptySlot = GetFirstEmptySlot();
            if (emptySlot != -1)
            {
                itemContainer[emptySlot] = item;
                numberOfItems++;
            }
        }
        else throw Error::InventoryFull(__FILE__, __FUNCTION__, __LINE__);
    }

    template<typename T, int size>
    T &Inventory<T, size>::GetItem(int slot)
    {
        if (slot >= 0 && slot < capacity) return itemContainer[slot];
        else throw Error::OutOfRange(__FILE__, __FUNCTION__, __LINE__);
    }

    template<typename T, int size>
    T Inventory<T, size>::RemoveItem(int slot)
    {
        if (slot >= 0 && slot < capacity && itemContainer[slot] != nullptr)
        {
            T removedItem = itemContainer[slot];
            itemContainer[slot] = nullptr;
            numberOfItems--;
            return removedItem;
        }
        else throw Error::OutOfRange(__FILE__, __FUNCTION__, __LINE__);
    }

    template<typename T, int size>
    void Inventory<T, size>::ResetInventory()
    {
        for (int i = 0; i < capacity; ++i)
        {
            itemContainer[i] = nullptr;
            numberOfItems = 0;
        }

        for (int i = 0; i < equipmentSlots; ++i)
        {
            equipmentContainer[i] = nullptr;
        }
    }

    template<typename T, int size>
    void Inventory<T, size>::EquipItem(T item)
    {
        if (item->GetItemType() == Items::ItemType::EQUIPPABLE) // check if item can be equipped
        {
            switch (item->GetDesiredEquipmentSlot()) // set item into slot
            {
                case Items::DesiredEquipmentSlot::HAT:
                    if (equipmentContainer[0] == nullptr) equipmentContainer[Items::DesiredEquipmentSlot::HAT] = item;
                    else throw Error::InventoryFull(__FILE__, __FUNCTION__, __LINE__);
                    break;
                case Items::DesiredEquipmentSlot::HONEY:
                    if (equipmentContainer[1] == nullptr) equipmentContainer[Items::DesiredEquipmentSlot::HONEY] = item;
                    else throw Error::InventoryFull(__FILE__, __FUNCTION__, __LINE__);
                    break;
                case Items::DesiredEquipmentSlot::SHOES:
                    if (equipmentContainer[2] == nullptr) equipmentContainer[Items::DesiredEquipmentSlot::SHOES] = item;
                    else throw Error::InventoryFull(__FILE__, __FUNCTION__, __LINE__);
                    break;
            }

            // delete the item from the inventory
            for (int i = 0; i < capacity; ++i)
            {
                if (itemContainer[i] == item)
                {
                    itemContainer[i] = nullptr;
                    numberOfItems--;
                    break;
                }
            }
        }
        else throw Error::EquipmentError(__FILE__, __FUNCTION__, __LINE__);
    }

    template<typename T, int size>
    void Inventory<T, size>::UnequipItem(int slot)
    {
        if (slot >= 0 && slot < equipmentSlots) // check if slot is valid
        {
            if (equipmentContainer[slot] != nullptr) // check if slot is already empty
            {
                if (numberOfItems < capacity) // check if inventory has capacity to catch unequipped item
                {
                    equipmentContainer[slot] = nullptr;
                    numberOfItems++;
                }
                else throw Error::InventoryFull(__FILE__, __FUNCTION__, __LINE__);
            }
            else throw Error::EquipmentError(__FILE__, __FUNCTION__, __LINE__);
        }
        else throw Error::OutOfRange(__FILE__, __FUNCTION__, __LINE__);
    }

    template<typename T, int size>
    int Inventory<T, size>::GetFirstEmptySlot()
    {
        for (int i = 0; i < GetCapacity(); ++i)
        {
            if (itemContainer[i] == nullptr) return i;
        }
        return -1; // if there is no empty slot return -1
    }

    /*** SORT-ALGORITHM ***/
    template<typename T, int size>
    void Inventory<T, size>::SortForWeight()
    {
        for (int i = capacity; i > 1; --i)
        {
            for (int j = 0; j < i - 1; ++j)
            {
                // if both slots have an item, swap them
                if (itemContainer[j] != nullptr && itemContainer[j + 1] != nullptr)
                {
                    if (itemContainer[j]->GetWeight() < itemContainer[j + 1]->GetWeight())
                    {
                        T temporaryItem = itemContainer[j];
                        itemContainer[j] = itemContainer[j + 1];
                        itemContainer[j + 1] = temporaryItem;
                    }
                }
                // if the current slot does not contain an item, but the next one does, put the item one slot further
                else if (itemContainer[j] == nullptr && itemContainer[j + 1] != nullptr)
                {
                    itemContainer[j] = itemContainer[j + 1];
                    itemContainer[j + 1] = nullptr;
                }
            }
        }
    }

    template<typename T, int size>
    void Inventory<T, size>::SortForName()
    {
        for (int i = capacity; i > 1; --i)
        {
            for (int j = 0; j < i - 1; ++j)
            {
                // if both slots have an item, swap them
                if (itemContainer[j] != nullptr && itemContainer[j + 1] != nullptr)
                {
                    if (itemContainer[j]->GetName() > itemContainer[j + 1]->GetName())
                    {
                        T temporaryItem = itemContainer[j];
                        itemContainer[j] = itemContainer[j + 1];
                        itemContainer[j + 1] = temporaryItem;
                    }
                }
                // if the current slot does not contain an item, but the next one does, put the item one slot further
                else if (itemContainer[j] == nullptr && itemContainer[j + 1] != nullptr)
                {
                    itemContainer[j] = itemContainer[j + 1];
                    itemContainer[j + 1] = nullptr;
                }
            }
        }
    }

    template<typename T, int size>
    void Inventory<T, size>::SortForCost()
    {
        for (int i = capacity; i > 1; --i)
        {
            for (int j = 0; j < i - 1; ++j)
            {
                // if both slots have an item, swap them
                if (itemContainer[j] != nullptr && itemContainer[j + 1] != nullptr)
                {
                    if (itemContainer[j]->GetCost() < itemContainer[j + 1]->GetCost())
                    {
                        T temporaryItem = itemContainer[j];
                        itemContainer[j] = itemContainer[j + 1];
                        itemContainer[j + 1] = temporaryItem;
                    }
                }
                // if the current slot does not contain an item, but the next one does, put the item one slot further
                else if (itemContainer[j] == nullptr && itemContainer[j + 1] != nullptr)
                {
                    itemContainer[j] = itemContainer[j + 1];
                    itemContainer[j + 1] = nullptr;
                }
            }
        }
    }

}
