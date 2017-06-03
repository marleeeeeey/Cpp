#pragma once

#include <bitset>
#include <iostream>


template<size_t _bits>
class bitsetadv
{    
public:
    typedef std::bitset<_bits> StdBitSet;

    void setBit(unsigned numBit)
    {
        m_data[numBit] = true;
    }

    void resetBit(unsigned numBit)
    {
        m_data[numBit] = false;
    }

    bool getBit(unsigned numBit) const 
    {
        return m_data[numBit];
    }

    void setLeftBit(unsigned numBit)
    {
        setBit(leftBit(numBit));
    }

    void resetLeftBit(unsigned numBit)
    {
        resetBit(leftBit(numBit));
    }

    bool getLeftBit(unsigned numBit) const
    {
        return getBit(leftBit(numBit));
    }

    StdBitSet getBitSet() const { return m_data; }

private:
    unsigned leftBit(unsigned stdNumBit) const
    {
        return _bits - stdNumBit - 1;
    }

    StdBitSet m_data;
};

template<size_t _bits>
std::ostream & operator<<(std::ostream & os, const bitsetadv<_bits> & bsa)
{
    os << "0x" << std::hex << bsa.getBitSet().to_ullong() << std::dec;
    return os;
}