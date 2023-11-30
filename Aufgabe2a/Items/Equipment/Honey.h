#pragma once

#include "EquippableItem.h"

namespace Items
{

    class Honey : public EquippableItem
    {
    public:
        Honey()
        {
            SetWeight(3);
            SetCost(4);
            SetName("Honey");
            SetDesc("A sweet dip. Gives you +4 strength");
            SetStrength(4);
            SetItemType(ItemType::EQUIPPABLE);
            SetEquipmentSlot(DesiredEquipmentSlot::HONEY);
        }

    };

}