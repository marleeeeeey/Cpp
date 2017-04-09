#pragma once
#include "StdHelper.hpp"

namespace SizeOf
{
    struct TestUsLL
    {
        unsigned short us;
        long long ll;
    };

    struct TestChInt
    {
        char ch;
        int i;
    };

#pragma pack(push, 1) // exact fit - no padding
    struct MyStruct
    {
        char b;
        int a;
        int array[2];
    };
#pragma pack(pop) //back to whatever the previous packing mode was 



    void resolve()
    {
        AFUN;

        int arr[10];

        AMSG("int arr[10];")
        AVAR(sizeof(arr));
        AVAR(sizeof(int));
        AVAR(sizeof(*arr));


        ASPLIT;

        AVAR(sizeof(char));
        AVAR(sizeof(int) );
        AVAR(sizeof(long));
        AVAR(sizeof(short));
        AVAR(sizeof(long long));

        ASPLIT;

        TestUsLL usLL;
        AVAR(sizeof(usLL));
        AVAR(sizeof(TestUsLL));
        AVAR(sizeof(usLL.us));
        AVAR(sizeof(usLL.ll));

        ASPLIT;

        TestChInt chInt;
        AVAR(sizeof(chInt));
        AVAR(sizeof(TestChInt));
        AVAR(sizeof(chInt.ch));
        AVAR(sizeof(chInt.i));

        ASPLIT;

        MyStruct chIntArr;
        AVAR(sizeof(chIntArr));
        AVAR(sizeof(MyStruct));
        AVAR(sizeof(chIntArr.a));
        AVAR(sizeof(chIntArr.b));
        AVAR(sizeof(chIntArr.array));

        ASPLIT;

		AVAR(sizeof(1UL));
		AVAR(sizeof(1ULL));

    }
}

