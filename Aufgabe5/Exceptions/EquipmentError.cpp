#include "EquipmentError.h"

namespace Error
{

    const char* EquipmentError::what() const noexcept
    {
        return this->outputMsg.c_str();
    }

}