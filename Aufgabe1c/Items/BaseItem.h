#pragma once

#include <string>
#include "raylib.h"
#include "../GameObject.h"

namespace Items
{

    class BaseItem : public GameObject
    {
    public:

        void SetWeight(float weight) { this->weight = weight; }
        float GetWeight() { return this->weight; }

        void SetCost(float cost) { this->cost = cost; }
        float GetCost() { return this->cost; }

        void SetName(std::string name) { this->name = name; }
        std::string GetName() { return this->name; }

        void SetDesc(std::string description) { this->description = description; }
        std::string GetDesc() { return this->description; }

    protected:
        float weight;
        float cost;
        std::string name;
        std::string description;
    };

}