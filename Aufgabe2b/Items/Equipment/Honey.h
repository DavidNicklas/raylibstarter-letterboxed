#pragma once

#include "EquippableItem.h"

namespace Items
{

    class Honey : public EquippableItem
    {
    public:
        Honey()
        {
            texture.ChangeTexture("../../assets/graphics/honey.png");

            SetWeight(4);
            SetCost(10);
            SetName("Honey");
            SetDesc("A sweet dip. Gives you +4 strength");
            SetStrength(4);
            SetItemType(ItemType::EQUIPPABLE);
            SetEquipmentSlot(DesiredEquipmentSlot::HONEY);
        }

    };

}