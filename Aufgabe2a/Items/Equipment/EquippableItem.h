#pragma once

#include "../BaseItem.h"


namespace Items
{

    class EquippableItem : public BaseItem
    {
    public:
        void SetStrength(int strength) { this->additionalStrength = strength; }
        int GetStrength() { return this->additionalStrength; }

    protected:
        int additionalStrength;


    };

}
