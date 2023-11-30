#pragma once

#include "iostream"
#include <sstream>

namespace Error
{

    class InventoryFull : public std::exception
    {
    private:
        std::string file;
        std::string function;
        std::string desc;
        int line;
        std::string outputMsg;

    public:
        InventoryFull(const char *inFile, const char *inFunction, int inLine)
        {
            this->desc = "Inventory full";
            this->file = inFile;
            this->function = inFunction;
            this->line = inLine;

            std::stringstream outputMsgSS;
            outputMsgSS << "*****************************\n" << "Error: " << desc << "\nException in file: " << file << "\nFunction: " << function
                        << "\nIn line: " << line << "\n*****************************" << std::endl;
            this->outputMsg = outputMsgSS.str();
        }

        const char *what() const noexcept override;
    };

}