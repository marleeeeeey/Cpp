#pragma once

#include "StdInclude.h"


class OneLogStream
{
public:
    typedef vector<ostream *> Ostreams;
    inline static OneLogStream & instanse()
    {
        static OneLogStream onlyOne;
        return onlyOne;
    }
    
    inline void setOstreams(Ostreams & ostreams) { m_ostreams = ostreams; }
    inline Ostreams & getOstreams() { return m_ostreams; }

private:
    OneLogStream() {}
    ~OneLogStream() {}
    OneLogStream(const OneLogStream & other) = delete;
    void operator=(const OneLogStream & other) = delete;

    Ostreams m_ostreams;
};


template<typename T>
OneLogStream & operator<<(OneLogStream & lg, const T /*& */d)
{
    for (ostream * pOst : lg.getOstreams())
    {
        ostream & ost = *pOst;
        ost << d;
    }

    return lg;
}
