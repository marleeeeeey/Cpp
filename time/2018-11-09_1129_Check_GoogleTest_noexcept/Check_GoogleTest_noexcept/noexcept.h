#define _ALLOW_KEYWORD_MACROS

#if _MSC_VER < 1900
#define noexcept throw()
#else
#define noexcept noexcept
#pragma  message("Noexcept time bomb activated")
#endif
