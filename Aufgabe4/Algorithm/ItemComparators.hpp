#pragma once

template<typename T>
bool CompareByWeight(const T& item1, const T& item2)
{
    return (item1->GetWeight() < item2->GetWeight());
}

template<typename T>
bool CompareByName(const T& item1, const T& item2)
{
    return (item1->GetName() > item2->GetName());
}

template<typename T>
bool CompareByCost(const T& item1, const T& item2)
{
    return (item1->GetCost() < item2->GetCost());
}