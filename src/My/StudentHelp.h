#pragma once



namespace StudentHelp
{
    void resolve()
    {
        AFUN;

        int a = 5;
        int b = 10;
        int sum = a + b;

        AVAR(sum);

        if (sum > 10)
        {
            AMSG("hello");
        }
        else
        {
            if (sum > 12)
            {
                AMSG("goodbye");
            }
        }
    }

}
