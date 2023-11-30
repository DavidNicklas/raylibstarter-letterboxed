#include "InventoryFull.h"

namespace Error
{

    const char *InventoryFull::what() const noexcept
    {
        return this->outputMsg.c_str();
    }

}

