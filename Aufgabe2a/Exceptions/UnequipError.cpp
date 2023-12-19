#include "UnequipError.h"

namespace Error
{

    const char *UnequipError::what() const noexcept
    {
        return this->outputMsg.c_str();
    }

}