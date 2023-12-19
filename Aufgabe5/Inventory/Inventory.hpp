#include "Inventory.h"
#include "../Algorithm/Bubblesort.hpp"
#include "../Algorithm/ItemComparators.hpp"

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
            int emptySlot = GetFirstEmptySlot(); // calculates the first empty slot in the array so items are filled in gaps
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
                    if (equipmentContainer[0] == nullptr)
                    {
                        equipmentContainer[Items::DesiredEquipmentSlot::HAT] = item;
                        DeleteItemFromInventory(item);
                    }
                    // If there is already an item, they can be swapped out if newItem has more strength
                    // than the item in the slot
                    else if (std::dynamic_pointer_cast<Items::EquippableItem>(equipmentContainer[0]) && std::dynamic_pointer_cast<Items::EquippableItem>(item))
                    {
                        // If the items can be cast correctly, compare the strength values
                        SwapEquipmentItem(item, equipmentContainer[0], Items::DesiredEquipmentSlot::HAT);
                    }
                    break;

                case Items::DesiredEquipmentSlot::HONEY:
                    if (equipmentContainer[1] == nullptr)
                    {
                        equipmentContainer[Items::DesiredEquipmentSlot::HONEY] = item;
                        DeleteItemFromInventory(item);
                    }
                    // If there is already an item, they can be swapped out if newItem has more strength
                    // than the item in the slot
                    else if (std::dynamic_pointer_cast<Items::EquippableItem>(equipmentContainer[1]) && std::dynamic_pointer_cast<Items::EquippableItem>(item))
                    {
                        // If the items can be cast correctly, compare the strength values
                        SwapEquipmentItem(item, equipmentContainer[1], Items::DesiredEquipmentSlot::HONEY);
                    }
                    break;

                case Items::DesiredEquipmentSlot::SHOES:
                    if (equipmentContainer[2] == nullptr)
                    {
                        equipmentContainer[Items::DesiredEquipmentSlot::SHOES] = item;
                        DeleteItemFromInventory(item);
                    }
                    // If there is already an item, they can be swapped out if newItem has more strength
                    // than the item in the slot
                    else if (std::dynamic_pointer_cast<Items::EquippableItem>(equipmentContainer[2]) && std::dynamic_pointer_cast<Items::EquippableItem>(item))
                    {
                        // If the items can be cast correctly, compare the strength values
                        SwapEquipmentItem(item, equipmentContainer[2], Items::DesiredEquipmentSlot::SHOES);
                    }
                    break;
            }
        }
        else throw Error::EquipmentError(__FILE__, __FUNCTION__, __LINE__);
    }

    template<typename T, int size>
    void Inventory<T, size>::DeleteItemFromInventory(T item)
    {
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

    template<typename T, int size>
    void Inventory<T, size>::SwapEquipmentItem(T& itemToSwap, T& itemInSlot, Items::DesiredEquipmentSlot slot)
    {
        std::shared_ptr<Items::EquippableItem> slotItem = std::dynamic_pointer_cast<Items::EquippableItem>(itemInSlot);
        std::shared_ptr<Items::EquippableItem> pickedUpItem = std::dynamic_pointer_cast<Items::EquippableItem>(itemToSwap);
        if (slotItem->GetAdditionalStrength() < pickedUpItem->GetAdditionalStrength())
        {
            AddItem(itemInSlot); // Add the item currently in the equipment slot to the inventory
            equipmentContainer[slot] = itemToSwap; // Put the new item in the equipment slot
            DeleteItemFromInventory(itemToSwap); // Delete the new item from the inventory
        }
        else throw Error::InventoryFull(__FILE__, __FUNCTION__, __LINE__);
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
        Algorithm::BubbleSort(itemContainer, capacity, CompareByWeight<T>);
    }

    template<typename T, int size>
    void Inventory<T, size>::SortForName()
    {
        Algorithm::BubbleSort(itemContainer, capacity, CompareByName<T>);
    }

    template<typename T, int size>
    void Inventory<T, size>::SortForCost()
    {
        Algorithm::BubbleSort(itemContainer, capacity, CompareByCost<T>);
    }

}
