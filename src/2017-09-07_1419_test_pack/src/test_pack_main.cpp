#include "StdPlus\StdPlus.h"

unsigned long f2u(float value, float mass, unsigned char Bits, unsigned char PosLowBit)
{
    unsigned long mask, parm;
    if (value == 0. || value < 0. || mass == 0. || Bits == 0) return 0;
    mask = (1UL << Bits) - 1UL;
    //sw преобразование float -> unsigned long для n<0 = 0!
    parm = (unsigned long)((long)(value / mass * (1UL << (Bits - 1)) + .5));
    if (parm > mask) return mask << PosLowBit;
    return parm << PosLowBit;
}

unsigned long f2s(float value, float mass, unsigned char Bits, unsigned char PosLowBit)
{
    AVAR(value);
    AVAR(mass);
    AVAR((int)Bits);
    AVAR((int)PosLowBit);
    ASPACE;

    unsigned long mask, parm;

    if (value == 0. || mass == 0. || Bits == 0) return 0;
    /* возвращаем беззнаковое значение  */
    if (value > 0.) return f2u(value, mass, Bits - 1, PosLowBit);
    /* возвращаем знаковое значение */
    mask = ~((1UL << (Bits - 1)) - 1UL);
    //sw преобразование float -> unsigned long для n<0 = 0!
    auto val1 = 1UL << (Bits - 2);
    auto val2 = value / mass;
    auto val3 = val2 * val1;
    auto val4 = val3 - .5;
    parm = (unsigned long)((long)val4);

    AHEX(val1);
    AVAR(val2);
    AVAR(val3);
    AVAR(val4);
    AHEX(mask);
    AHEX(parm);

    if ((parm > mask) || (parm == 0))
    {
        auto val1 = (1UL << Bits);
        auto val2 = val1 - 1UL;
        auto val3 = parm & val2;
        auto val4 = val3 << PosLowBit;

        AHEX(val1);
        AHEX(val2);
        AHEX(val3);
        AHEX(val4);

        return val4;
    }
    return (mask & ((1UL << Bits) - 1UL)) << PosLowBit;
}

void test01()
{
    AHEX(0UL - 1);
}

void test02()
{
    for (auto i : { 0, 1, 2, 30, 31, 32 })
    {
        auto result = f2s(-1, 1, 1, i);
        AHEX(result);
        ASPLIT;
    }
}

void test03()
{
    for (int i = 0; i <= 32; ++i)
    {
        auto mask1 = ~((1UL << (i - 1)) - 1UL);
        auto mask2 = 1UL << (i - 1);

        AVAR(i);
        AHEX(mask1);
        AHEX(mask2);
    }
}

int main()
{
    test01();
    ASPLIT;

    test02();
    ASPLIT;

    test03();
    ASPLIT;

    APAUSE;
}
