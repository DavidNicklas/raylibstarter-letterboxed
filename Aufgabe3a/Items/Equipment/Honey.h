#pragma once

#include "EquippableItem.h"

namespace Items
{

    class Honey : public EquippableItem
    {
    public:
        Honey(Texture2D newTexture)
        {
            texture.ChangeTexture(newTexture);

            SetWeight(4);
            SetCost(10);
            SetName("Honey");
            SetDesc("A sweet dip. +4 strength");
            SetStrength(4);
            SetItemType(ItemType::EQUIPPABLE);
            SetEquipmentSlot(DesiredEquipmentSlot::HONEY);
        }
    };

}