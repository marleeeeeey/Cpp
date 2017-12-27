#pragma once



namespace SkienaChapter02
{
    void logTest()
    {
        AFUN;

        float a       = 1000;
        float logA    = log(a);
        float logTenA = log10(a);

        AVAR(a);
        AVAR(logA);
        AVAR(logTenA);

        ASPACE;

        float e       = 2.7183f;
        float logE    = log(e);
        float logTenE = log10(e);

        AVAR(e);
        AVAR(logE);
        AVAR(logTenE);

    }


    void resolve()
    {
        AFUN;
        logTest();
    }
}