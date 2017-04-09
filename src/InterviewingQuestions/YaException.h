#pragma once

namespace YaException
{
    void throwExceptionStd()
    {
        throw(std::exception());
    }

    void throwInteger()
    {
        throw(int(10));         // Выбрасывать можно любой объект
    }                           // Но для удобства лучше наследоваться
                                // от std::Exception.
                                // catch(...) перехватывает все!!!

    void resolve()              
    {
        AFUN;

        try
        {
            AMSG("In try");
            //throwExceptionStd();
            throwInteger();
        }
        catch (std::exception &)
        {
            AMSG("In catch (std::exception &)");
        }
        catch (...)
        {
            AMSG("catch (...)");
        }

    }
}