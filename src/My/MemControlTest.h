#pragma once

#include "StdHelper.hpp"

namespace MemControlTest
{
//     template<typename BType, size_t e_size=1>
//     class BSet
//     {
//     public:
//         BSet(BType * ws)
//             : m_words(ws)
//         {
//             m_countBits = sizeof_bit(m_words, e_size);
//             m_wordSize_bit = sizeof_bit(m_words);            
//         }
// 
//         void print()
//         {
//             for (int i = 0; i < e_size; ++i)
//             {
//                 AHEX((unsigned)m_words[i])
//             }
//         }
// 
//         inline void setBit(unsigned numBit)
//         {
//             checkNumBit(numBit);            
//             curWord(numBit) |= bitMask(numBit);
//         }
// 
//         inline void resetBit(unsigned numBit)
//         {
//             checkNumBit(numBit);
//             curWord(numBit) &= ~bitMask(numBit);
//         }
// 
//         inline void switchBit(unsigned numBit)
//         {
//             checkNumBit(numBit);
//             curWord(numBit) ^= bitMask(numBit);
//         }
//         
//         inline bool isBit(unsigned numBit)
//         {
//             checkNumBit(numBit);
//             return curWord(numBit) & bitMask(numBit);
//         }
// 
//     private:
//         inline void throwErrorBits() { throw(std::logic_error("error bits")); }
//         inline void checkNumBit(unsigned numBit) 
//         {
//             if (numBit < 0 || numBit >= m_countBits)
//                 throwErrorBits();
//         }
//         inline unsigned numWord(unsigned numBit) { return numBit / m_wordSize_bit; }
//         inline BType & curWord(unsigned numBit) { return m_words[numWord(numBit)]; }
//         inline size_t numBitInWord(unsigned numBit) { return numBit % m_wordSize_bit; }
//         inline BType bitMask(unsigned numBit) 
//         {
//             BType bm = 1;
//             bm = bm << numBitInWord(numBit);
//             return bm;
//         }
// 
//         BType * m_words;
//         size_t  m_countBits    = -1;
//         size_t  m_wordSize_bit = -1;
//     };

    void resolve()
    {
        AFUN;

        enum { curSize = 3 };

        typedef unsigned BType;

        BType ch[curSize];
        memset(ch, 0, sizeof(ch));

        BSet<BType, curSize> b(ch);

        for (unsigned i = 0; i <= 23; ++i)
        {
            AVAR(i);

            AMSG("setBit");
            b.setBit(i);

            b.print();
            AVAR(b.isBit(i));
            
            AMSG("resetBit");
            b.resetBit(i);

            b.print();
            AVAR(b.isBit(i));
            
            ASPACE;
        }
    }
}

