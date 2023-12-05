#pragma once

#include "BaseItem.h"

namespace Items
{

    class Fish : public BaseItem
    {
    public:
        Fish(Texture2D newTexture)
        {
            texture.ChangeTexture(newTexture);

            SetWeight(4);
            SetCost(8);
            SetName("Fish");
            SetDesc("It is good for mental health");
            SetItemType(ItemType::NOT_EQUIPPABLE);
        }
    };

}