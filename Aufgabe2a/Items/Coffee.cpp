#include "Coffee.h"

Items::Coffee::Coffee()
{
    SetWeight(1);
    SetCost(3);
    SetName("Coffee");
    SetDesc("If you are tired, this coffee gives you a huge kick");
    SetItemType(ItemType::NOT_EQUIPPABLE);
}