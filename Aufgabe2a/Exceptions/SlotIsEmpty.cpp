#include "SlotIsEmpty.h"

namespace Error
{

    const char *SlotIsEmpty::what() const noexcept
    {
        return this->outputMsg.c_str();
    }

}