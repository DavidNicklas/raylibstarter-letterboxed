#pragma once

#include "BaseItem.h"

namespace Items
{

    class Coffee : public BaseItem
    {
    public:
        Coffee()
        {
            texture.ChangeTexture("../../assets/graphics/coffee.png");

            SetWeight(1);
            SetCost(3);
            SetName("Coffee");
            SetDesc("If you are tired, this coffee gives you a huge kick");
            SetItemType(ItemType::NOT_EQUIPPABLE);
        }
    };

}