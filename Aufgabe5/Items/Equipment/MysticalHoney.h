#pragma once

#include "EquippableItem.h"

namespace Items
{

    class MysticalHoney : public EquippableItem
    {
    public:
        MysticalHoney(Texture2D newTexture)
        {
            texture.ChangeTexture(newTexture);

            SetWeight(8);
            SetCost(99);
            SetName("Mystical Honey");
            SetDesc("A mystical dip. +7 strength");
            SetStrength(7);
            SetItemType(ItemType::EQUIPPABLE);
            SetEquipmentSlot(DesiredEquipmentSlot::HONEY);
        }
    };

}