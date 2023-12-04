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
            SetDesc("A delicious meal to safe proteins");
            SetItemType(ItemType::NOT_EQUIPPABLE);
        }
    };

}