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

            SetWeight(2);
            SetCost(1);
            SetName("Coffee");
            SetDesc("Good if you are tired");
            SetItemType(ItemType::NOT_EQUIPPABLE);
        }
    };

}