#pragma once

#include "BaseItem.h"

namespace Items
{

    class Coffee : public BaseItem
    {
    public:
        Coffee(float weight = 0.0f, float cost = 0.0f, std::string name = " ", std::string description = " ");

        void Update() override {};
        void Draw() override {};

    private:

    };

}