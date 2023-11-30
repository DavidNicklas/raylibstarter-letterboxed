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
            itemContainer[numberOfItems] = item;
            numberOfItems++;
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


}
