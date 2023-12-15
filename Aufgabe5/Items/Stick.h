#pragma once

#include "BaseItem.h"

namespace Items
{

    class Stick : public BaseItem
    {
    public:
        Stick(Texture2D newTexture)
        {
            texture.ChangeTexture(newTexture);

            SetWeight(1);
            SetCost(3);
            SetName("Stick");
            SetDesc("Just a simple stick");
            SetItemType(ItemType::NOT_EQUIPPABLE);
        }
    };

}