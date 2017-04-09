#pragma once

#include "StdHelper.hpp"

namespace HelperLibTest
{
    void resolve()
    {
        AFUN;

        oneHelperLibData().m_isPrintLine = true;

        std::map<int, string> strings =
        {
            { 1, "asd" },
            { 5, "rherthert" },
            { 4, "yjtyj" },
            { 7, "cvbcvbcv" },
            { 9, "qwtqerhe" },
        };

        AVAR(strings);


        std::vector<string> strs
        {
            "asfasdf", 
            "tertwertwehwe", 
            "dfgsdfg", 
            "hqerhgehqerh",
        };

        AVAR(strs);

    }
}