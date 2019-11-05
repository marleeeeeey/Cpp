#include "StdPlus/MacrosPlus.hpp"

template<typename T>
T left_shift(T value, unsigned short int bits)
{
    AFUN;

    if (bits >= sizeof(T)*8)
    {
        value = 0;
    }
    else
    {
        value = value << bits;
    }

    return value;
}

//#include "StdPlus\MacrosPlus.hpp"
//
//unsigned long f2u(float value, float mass, unsigned char Bits, unsigned char PosLowBit)
//{
//    unsigned long mask, parm;
//    if (value == 0. || value < 0. || mass == 0. || Bits == 0) return 0;
//    mask = (1UL << Bits) - 1UL;
//    //sw преобразование float -> unsigned long для n<0 = 0!
//    parm = (unsigned long)((long)(value / mass * (1UL << (Bits - 1)) + .5));
//    if (parm > mask) return mask << PosLowBit;
//    return parm << PosLowBit;
//}
//
//unsigned long f2s(float value, float mass, unsigned char Bits, unsigned char PosLowBit)
//{
//    AVAR(value);
//    AVAR(mass);
//    AVAR((int)Bits);
//    AVAR((int)PosLowBit);
//    ASPACE;
//
//    unsigned long mask, parm;
//
//    if (value == 0. || mass == 0. || Bits == 0) return 0;
//    /* возвращаем беззнаковое значение  */
//    if (value > 0.) return f2u(value, mass, Bits - 1, PosLowBit);
//    /* возвращаем знаковое значение */
//    mask = ~((1UL << (Bits - 1)) - 1UL);
//    //sw преобразование float -> unsigned long для n<0 = 0!
//    auto val1 = 1UL << (Bits - 2);
//    auto val2 = value / mass;
//    auto val3 = val2 * val1;
//    auto val4 = val3 - .5;
//    parm = (unsigned long)((long)val4);
//
//    AHEX(val1);
//    AVAR(val2);
//    AVAR(val3);
//    AVAR(val4);
//    AHEX(mask);
//    AHEX(parm);
//
//    if ((parm > mask) || (parm == 0))
//    {
//        auto val1 = (1UL << Bits);
//        auto val2 = val1 - 1UL;
//        auto val3 = parm & val2;
//        auto val4 = val3 << PosLowBit;
//
//        AHEX(val1);
//        AHEX(val2);
//        AHEX(val3);
//        AHEX(val4);
//
//        return val4;
//    }
//    return (mask & ((1UL << Bits) - 1UL)) << PosLowBit;
//}
//
//void test01()
//{
//    AHEX(0UL - 1);
//}
//
//void test02()
//{
//    auto result = f2s(-45, 45, 32, 0);
//    AHEX(result);
//}
//
//void test03()
//{
//    for (int i = 0; i <= 32; ++i)
//    {
//        auto mask1 = ~((1UL << (i - 1)) - 1UL);
//        auto mask2 = 1UL << (i - 1);
//
//        AVAR(i);
//        AHEX(mask1);
//        AHEX(mask2);
//    }
//}
//
//void test04()
//{
//    unsigned long a = 0x12345678;
//    AHEX(a);
//
//    short st = a >> 16;
//    short ml = a;
//
//    AHEX(st);
//    AHEX(ml);
//}
//
//void test05()
//{
//    AMSG("input '777' for exit");
//    unsigned long a = 1;
//    while (a != 777)
//    {
//        ARED(a);
//        AHEX(a);
//
//        short st = a >> 16;
//        short ml = a;
//
//        AHEX(st);
//        AHEX(ml);
//    }
//}
//
//void test06()
//{
//    for (int i = 0; i <= 33; i++)
//    {
//        auto val = (1UL << i);
//        AHEX(val);
//    }
//}

void test07()
{
    short i = 0x00000001;
    AHEX(i);
    AHEX(i << 32);
    AHEX(left_shift(i, 32));
    AHEX(i << 40);
    AHEX(left_shift(i, 40));
    AHEX(i << 20);
    AHEX(left_shift(i, 20));
    AHEX(i << 10);
    AHEX(left_shift(i, 10));

    long long long_value = 1;
    AHEX(long_value);
    AHEX(long_value << 32);
    AHEX(left_shift(long_value, 32));
    AHEX(long_value << 63);
    AHEX(left_shift(long_value, 63));
    AHEX(long_value << 64);
    AHEX(left_shift(long_value, 64));
    AHEX(long_value << 66);
    AHEX(left_shift(long_value, 66));
    AHEX(long_value << 20);
    AHEX(left_shift(long_value, 20));
    AHEX(long_value << 10);
    AHEX(left_shift(long_value, 10));
}

void test08()
{
    short i = 0x8000;
    AHEX(i);
    AHEX(i >> 32);
    AHEX(left_shift(i, 32));
    AHEX(i >> 40);
    AHEX(left_shift(i, 40));
    AHEX(i >> 20);
    AHEX(left_shift(i, 20));
    AHEX(i >> 10);
    AHEX(left_shift(i, 10));

    long long long_value = (long long)1 >> 63;
    AHEX(long_value);
    AHEX(long_value >> 32);
    AHEX(left_shift(long_value, 32));
    AHEX(long_value >> 63);
    AHEX(left_shift(long_value, 63));
    AHEX(long_value >> 64);
    AHEX(left_shift(long_value, 64));
    AHEX(long_value >> 66);
    AHEX(left_shift(long_value, 66));
    AHEX(long_value >> 20);
    AHEX(left_shift(long_value, 20));
    AHEX(long_value >> 10);
    AHEX(left_shift(long_value, 10));
}

int main()
{
//     test01();
//     ASPLIT;
//
//     test02();
//     ASPLIT;
//
//     test03();
//     ASPLIT;
//
//     test04();
//     ASPLIT;
//
//     test05();
//     ASPLIT;

//    test06();

    //test07();

    test08();

    //AHEX(result);

    //APAUSE;
}
