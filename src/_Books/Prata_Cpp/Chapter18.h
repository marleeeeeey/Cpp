#include "StdHelper.hpp"

namespace PrataChapter18
{
    template<typename T>
    void showList(T value)
    {
        AVAR(value);
        ASPLIT;
    }

    template<typename T, typename... Args>
    void showList(T value, Args... args)
    {
        AVAR(value);
        showList(args...);
    }

    void resolve()
    {
        AFUN;

        int a = 10;
        double b = 54.2;
        string s = "mamba";

        showList(a, b, s);

        showList(s);
    }
}