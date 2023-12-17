#pragma once

#include "iostream"
#include <sstream>
#include <memory>

#include "../Items/BaseItem.h"

namespace Error
{

    class EquipmentError : public std::exception
    {
    private:
        std::string file;
        std::string function;
        std::string desc;
        int line;
        std::string outputMsg;
        std::shared_ptr<Items::BaseItem> equipItem;

    public:
        EquipmentError(const char *inFile, const char *inFunction, int inLine, std::shared_ptr<Items::BaseItem> equipItem)
        {
            this->equipItem = equipItem;
            this->file = inFile;
            this->function = inFunction;
            this->line = inLine;
            this->desc = "Can't equip/unequip item: " + equipItem->GetName();

            std::stringstream outputMsgSS;
            outputMsgSS << "*****************************\n" << "Error: " << desc << "\nException in file: " << file << "\nFunction: " << function
                        << "\nIn line: " << line << "\n*****************************" << std::endl;
            this->outputMsg = outputMsgSS.str();
        }

        const char *what() const noexcept override;
    };

}