#pragma once

#include "../BaseItem.h"


namespace Items
{

    class EquippableItem : public BaseItem
    {
    public:
        void SetStrength(int strength) { this->additionalStrength = strength; }

    private:
        int additionalStrength; // this stat increases the players strength, when equipped

    };

}
