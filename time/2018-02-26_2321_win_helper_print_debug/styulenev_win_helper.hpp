#include <sstream>

#define STYULENEV_OUT \
    { \
        std::wstringstream ss; \
        ss << "styulenev: "
#define STYULENEV_ENDL \
            ; \
        OutputDebugString(ss.str().c_str()); \
    }
#define STYULENEV_FUNC \
    STYULENEV_OUT \
        << "func=" << __FUNCTION__ \
    STYULENEV_ENDL

inline
std::basic_ostream<wchar_t> & operator<<(std::basic_ostream<wchar_t>& os, const tagRECT& rect)
{
    os
        << "("
        << rect.left << ", "
        << rect.top << ", "
        << rect.right << ", "
        << rect.bottom
        << ")"
        ;

    return os;
}

inline 
std::basic_ostream<wchar_t> & operator<<(std::basic_ostream<wchar_t>& os, const CPoint& point)
{
    os
        << "("
        << point.x << ", "
        << point.y << ", "
        << ")"
        ;

    return os;
}

//// Example:
//
// STYULENEV_OUT
//     << "m_ClientRectWorksetTree=" << m_ClientRectWorksetTree << ", "
//     << "point=" << point
// STYULENEV_ENDL;