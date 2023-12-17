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

            SetWeight(4);
            SetCost(5);
            SetName("Raw Meat");
            SetDesc("A delicious meal to safe proteins");
            SetItemType(ItemType::NOT_EQUIPPABLE);
        }
    };

}