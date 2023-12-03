#pragma once

#include "EquippableItem.h"

namespace Items
{

    class Shoes : public EquippableItem
    {
    public:
        Shoes()
        {
            texture.ChangeTexture("../../assets/graphics/boots.png");

            SetWeight(7);
            SetCost(85);
            SetName("Sneakers");
            SetDesc("Comfort for your feet. Gives you +5 strength");
            SetStrength(5);
            SetItemType(ItemType::EQUIPPABLE);
            SetEquipmentSlot(DesiredEquipmentSlot::SHOES);
        }

    };

}