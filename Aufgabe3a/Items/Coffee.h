#pragma once

#include "BaseItem.h"

namespace Items
{

    class Coffee : public BaseItem
    {
    public:
        Coffee(Texture2D newTexture)
        {
            texture.ChangeTexture(newTexture);

            SetWeight(1);
            SetCost(3);
            SetName("Coffee");
            SetDesc("Good if you are tired");
            SetItemType(ItemType::NOT_EQUIPPABLE);
        }
    };

}