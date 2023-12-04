#pragma once

#include "EquippableItem.h"

namespace Items
{

    class Hat : public EquippableItem
    {
    public:
        Hat(Texture2D newTexture)
        {
            texture.ChangeTexture(newTexture);

            SetWeight(5);
            SetCost(40);
            SetName("Sleeping Hat");
            SetDesc("A nice hat, which fits well for sleep. Gives you +3 strength");
            SetStrength(3);
            SetItemType(ItemType::EQUIPPABLE);
            SetEquipmentSlot(DesiredEquipmentSlot::HAT);
        }
    };

}