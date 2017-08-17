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
        int bitPos = 1 << bitIndex;        
        int bit = ch & bitPos;
        bits.push_back(static_cast<bool>(bit));
    }
    
    return bits;
}

std::vector<bool> readVectorBoolFromBinFile(std::string & fileName, size_t countBit)
{
    std::ifstream ifs(fileName, std::ios_base::binary);
    if (!ifs.is_open())
        throw std::logic_error("ERROR: File '" + fileName + "' cannot open");

    ifs.seekg(0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    if (countBit > length * 8)
        throw std::logic_error("ERROR: Too small file '" + fileName + "'" 
            + " for countBit=" + std::to_string(countBit));

    char * buffer = new char[length];
    ifs.read(buffer, length);
    ifs.close();

    std::vector<bool> codes;
    codes.reserve(countBit);

    for (int i = 0; i < length; ++i)
    {
        char & ch = buffer[i];
        auto bits = charToVectorBool(ch);
        const size_t portionSize = std::min<size_t>(countBit, 8);
        codes.insert(codes.end(), bits.begin(), bits.begin() + portionSize);
        countBit -= portionSize;
        if (countBit == 0)
            break;
    }

    return codes;
}