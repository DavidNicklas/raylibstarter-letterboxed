#pragma once

#include "../BaseItem.h"


namespace Items
{

    enum DesiredEquipmentSlot {HAT, HONEY, SHOES};

    class EquippableItem : public BaseItem
    {
    public:
        void SetStrength(int strength) { this->additionalStrength = strength; }
        int GetStrength() { return this->additionalStrength; }

        void SetEquipmentSlot(DesiredEquipmentSlot slot) { this->desiredSlot = slot; }
        DesiredEquipmentSlot GetDesiredEquipmentSlot() { return this->desiredSlot; }

    protected:
        int additionalStrength;
        DesiredEquipmentSlot desiredSlot;


    };

}
