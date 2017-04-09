#pragma once

namespace TemplateParametr
{
    template<typename T>
    class TestStd
    {
    public:
        TestStd()
        {
            AFUN;
        }

        ~TestStd()
        {
            AFUN;
        }

    private:

    };

    template<int T>
    class TestInt
    {
    public:
        TestInt()
        {
            AFUN;
            AVAR(m_i);
        }

        ~TestInt()
        {
            AFUN;
            AVAR(m_i);
        }

    private:
        int m_i = T;

    };


    template<const char * T>
    class TestPChar
    {
    public:
        TestPChar()
        {
            AFUN;
            AVAR(m_i);
        }

        ~TestPChar()
        {
            AFUN;
            AVAR(m_i);
        }

    private:
        const char * m_i = T;

    };


    void resolve()
    {
        AFUN;

        TestStd<int> ti;
        TestStd<float> tf;

        TestInt<10> ti10;
        //TestPChar<"karamba\0"> tPChar10;
    }
}

