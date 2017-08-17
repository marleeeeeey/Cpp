#include "functions.h"


int one()
{
    return 1;
}

std::vector<bool> charToVectorBool(const char ch)
{
    std::vector<bool>bits;
    bits.reserve(8);

    for (int bitIndex = 7; bitIndex >= 0; --bitIndex)
    {
        char bit = 1 << bitIndex;
        bits.push_back(ch & bit);
    }
    
    return bits;
}

std::vector<bool> readVectorBoolFromBinFile(std::string & fileName, size_t countBit)
{
    std::vector<bool> codes;
    std::ifstream ifs(fileName);

    while (countBit > 0)
    {
        char ch;
        ifs >> ch;
        if (!ifs.good())
            break;
        auto bits = charToVectorBool(ch);
        const size_t portionSize = std::min<size_t>(countBit, 8);
        codes.insert(codes.end(), bits.begin(), bits.begin() + portionSize);
        countBit -= portionSize;
    }

    if (countBit > 0)
        throw std::logic_error("Error: Cannot read required number of bits from file '"
            + fileName + "'. LessCountBit=" + std::to_string(countBit));

    return codes;
}