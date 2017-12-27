#pragma once

#include "StdHelper.hpp"

class SpeakingClass
{
public:
    inline SpeakingClass(int var = 0)
    {
        m_var = var;
        m_id = getNewId();

        AFUN;
        AVAR(m_var);
        AVAR(m_id);
    }

    inline virtual ~SpeakingClass()
    {
        AFUN;
        AVAR(m_var);
        AVAR(m_id);
    }

    inline SpeakingClass(const SpeakingClass & other)
    {
        m_var  = other.m_var;
        m_id   = getNewId();

        AFUN;
        AVAR(m_var);
        AVAR(m_id);
    }

    inline const SpeakingClass & operator=(const SpeakingClass & other)
    {
        m_var  = other.m_var;
        m_id   = getNewId();

        AFUN;
        AVAR(m_var);
        AVAR(m_id);

        return *this;
    }
    
private:

    friend std::ostream & operator<<(std::ostream & os, const SpeakingClass & test);
    
    inline int getNewId()
    {
        static int m_genId = 0;
        return ++m_genId;
    }

    int m_id  = 0;
    int m_var = 0;
};

std::ostream & operator<<(std::ostream & os, const SpeakingClass & test)
{
    os 
        << "&="   << &test      << ", "
        << "id="  << test.m_id  << ", "
        << "var=" << test.m_var
        ;

    return os;
}
