#pragma once

#include "BaseItem.h"

namespace Items
{

    class Steak : public BaseItem
    {
    public:
        Steak(Texture2D newTexture)
        {
            texture.ChangeTexture(newTexture);

            SetWeight(2);
            SetCost(5);
            SetName("Steak");
            SetDesc("A delicious meal which gives you power for the day");
            SetItemType(ItemType::NOT_EQUIPPABLE);
        }
    };

}