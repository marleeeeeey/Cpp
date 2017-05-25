#pragma once

#include "StdHelper.hpp"

namespace SkienaChapter01
{
    void stdSort(string & s)
    {
        std::sort(s.begin(), s.end());
    }

    void insertionSort(string & s)      // p. 21
    {
        AVAR(s);

        for (size_t i = 1; i < s.length(); ++i)
        {
            size_t j = i;
            
            while (j > 0 && s[j - 1] > s[j])
            {
                std::swap(s[j - 1], s[j]);    
                j--;
            }

            AVAR(s);
        }
    }

    void resolve()
    {
        AFUN;
        
        typedef void(*PSortFun)(string &);

        struct FunParams
        {
            PSortFun pFun;
            string name;
            string result;
        };

        std::vector<FunParams> funs
        {
            { stdSort,       "stdSort",                          "" },
            { insertionSort, "insertionSort(page 21, page 137)", "" },
        };

        const string rawString = "karamba";
        AVAR(rawString);

        for (auto & fs : funs)
        {
            string str = rawString;
            fs.pFun(str);
            fs.result = str;
        }

        string correctResult = funs.front().result;
        AVAR(correctResult);

        for (auto it = funs.begin() + 1; it != funs.end(); it++)
        {
            ASPACE;
            string funName = it->name;
            AVAR(funName);

            string & curResult = it->result;
            if (curResult == correctResult)
            {
                AMSG("is Correct!");
            }
            else
            {
                AVAR(curResult);
                AMSG("is NOT Correct!");
            }
        }

        ASPACE;
    }
}