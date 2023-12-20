#pragma once

namespace Algorithm
{

    // The template parameter 'Comparator' is a type that represents a function or function-like object.
    // It is used to compare two elements in the container. The comparison is defined by the compareFunction
    template<class WhatToSort, typename Comparator>
    void BubbleSort(WhatToSort container[], int capacity, Comparator compareFunction)
    {
        for (int i = capacity; i > 1; --i)
        {
            for (int j = 0; j < i - 1; ++j)
            {
                // if both slots have an item, swap them
                if (container[j] != nullptr && container[j + 1] != nullptr)
                {
                    if (compareFunction(container[j], container[j + 1]))
                    {
                        WhatToSort temporaryItem = container[j];
                        container[j] = container[j + 1];
                        container[j + 1] = temporaryItem;
                    }
                }
                // if the current slot does not contain an item, but the next one does, put the item one slot further
                else if (container[j] == nullptr && container[j + 1] != nullptr)
                {
                    container[j] = container[j + 1];
                    container[j + 1] = nullptr;
                }
            }
        }
    }

}