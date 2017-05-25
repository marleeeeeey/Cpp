#pragma once

#include "StdHelper.hpp"

namespace SkienaExercises04
{
    void s01()
    {
        AFUN;

        enum { commandSize = 7 };
        int c1[commandSize] = { 4,6,7,4,5,8,2 };
        int c2[commandSize] = { 9,1,8,8,4,3,7 };

//         std::sort(c1, c1 + SIZEOF_ARR(c1));
//         std::sort(c2, c2 + SIZEOF_ARR(c2));        
    }
}

namespace SkienaChapter04
{
    using namespace SkienaShared;
    
    void resolveExercises()
    {
        AFUN;
        using namespace SkienaExercises04;

        s01();
    }

    int partition(item_type s[], int l, int h)
    {
        int i;
        int p;
        int firstHigh;
        p = h;
        firstHigh = l;

        for (int i = l; i < h; ++i)
        {
            if (s[i] < s[p])
            {
                std::swap(s[i], s[firstHigh]);
                firstHigh++;
            }
        }
        std::swap(s[p], s[firstHigh]);

        return firstHigh;
    }

    void quicksort(item_type s[], int l, int h)
    {
        int p;
        if ((h - l) > 0)
        {
            p = partition(s, l, h);
            quicksort(s, l, p - l);
            quicksort(s, p + l, h);
        }
    }

    void printArr(item_type * s, const size_t arrSize)
    {

        AVAR(arrSize);

        ostringstream os;

        for (int i = 0; i < arrSize; i++)
        {
            os << setw(3) << s[i] << ",";
        }

        AMSG(os.str());
    }

    void resolveChapter()
    {
        item_type s[] = { 4, 6, 5, 6, 4, 56, 2, 45, 6 };

//         const size_t arrSize = SIZEOF_ARR(s);
// 
//         AMSG("Before Sort");
//         printArr(s, arrSize);
// 
//         quicksort(s, arrSize / 2, arrSize - 1);
// 
//         AMSG("After Sorted");
//         printArr(s, arrSize);
    }

    void resolve()
    {
        AFUN;
        
        //resolveChapter();
        resolveExercises();

    }
}
