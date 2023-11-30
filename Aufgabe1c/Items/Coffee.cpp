#include "Coffee.h"

Items::Coffee::Coffee(float weight, float cost, std::string name, std::string description)
{
    this->weight = weight;
    this->cost = cost;
    this->name = name;
    this->description = description;
}