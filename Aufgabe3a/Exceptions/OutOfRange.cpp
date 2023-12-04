#include "OutOfRange.h"

namespace Error
{

    const char *OutOfRange::what() const noexcept
    {
        return this->outputMsg.c_str();
    }

}