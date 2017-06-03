#pragma once

#define DEBUG_ONLY_ERROR_off

#include "StdInclude.h"
#include "HelperLib.h"


#if !defined PROJECT_NAME
#define PROJECT_NAME "NoName"
#endif


#ifndef DEBUG_EXPORT
#    pragma comment(lib, "MyLogger.lib")
#    define DEBUG_API __declspec(dllimport)
#else 
#    define DEBUG_API __declspec(dllexport)
#endif 

#ifdef QT_CORE_LIB

# include "MyQtLogger.h"

#endif // QT_CORE_LIB

inline string funSigPrepare(string fs)
{
    string rem = removeFromString(fs, "__thiscall ");
    rem = removeFromString(rem, "__cdecl ");
    return rem;
}


#define FUNSIG funSigPrepare(__FUNCSIG__) 

inline std::ostream & voidOut()
{
    static std::ostream os(nullptr);
    return os;
}

DEBUG_API unsigned int _myDebugCounter();
DEBUG_API std::ostream & consoleOut(std::ostream * pCOUT = nullptr);
DEBUG_API std::ostream & logOut(std::ostream * pCOUT = nullptr);
DEBUG_API void russianConsole();

DEBUG_API void keep_window_open();
DEBUG_API void keep_window_open(std::string s);

DEBUG_API void startProgram(std::string programName = PROJECT_NAME);
DEBUG_API void endProgram(bool isAutoOpenReport = true, 
                          string notepadPath = "Notepad++\\notepad++.exe", 
                          const int exitCode = 0);

DEBUG_API void error(const std::string & errormessage = "unknow exception");
DEBUG_API void warning(const std::string & warningMessage = "unknow warning");

DEBUG_API std::string dateStr();
DEBUG_API std::string timeStr();
DEBUG_API std::string dateTimeStr();


#define CODE_POS_OUT_SHORT      FUNSIG << "   "
#define CODE_POS_OUT            __FILE__ <<  "(" <<  __LINE__ <<  ")   " << CODE_POS_OUT_SHORT

#define DOUT consoleOut() 

#define DVAR(var)\
     DOUT \
         << _myDebugCounter()\
         << " VAR " << #var << "=" << to_string(var) << std::endl

#define DHEX(var)\
     DOUT \
         << _myDebugCounter()\
         << " HEX " << #var << "=" << std::hex << (var) << /*to_string(var) <<*/ std::dec << std::endl

#define DMSG(var)\
     DOUT \
         << _myDebugCounter()\
         << " MSG " << to_string(var) << std::endl

#define DERR(var)\
     DOUT \
         << _myDebugCounter()\
         << " ERR " /*<< CODE_POS_OUT_SHORT*/ << to_string(var) << std::endl

#define DFUN\
     DOUT \
         << _myDebugCounter()\
         << " FUN " << FUNSIG << std::endl

#define DSPLIT\
     DOUT \
         << "\n---------------------------------------------------------------------------" \
         << std::endl

#define DSPACE\
     DOUT \
         << std::endl


#define LOUTCLEAN logOut() 
#define LOUT logOut() << timeStr()


#define LVAR(var)\
     LOUT \
         << "VAR " << #var << "=" << to_string(var) << std::endl

#define LHEX(var)\
     LOUT \
         << "HEX " << #var << "=" << std::hex << (var) << /*to_string(var) <<*/ std::dec << std::endl

#define LMSG(var)\
     LOUT \
         << "MSG " << to_string(var) << std::endl

#define LERR(var)\
     LOUT \
         << "ERR "  /*<< CODE_POS_OUT*/ << to_string(var) << std::endl

#define LFUN\
     LOUT \
         << "FUN " << FUNSIG << std::endl

#define LSPLIT\
     LOUTCLEAN \
         << "\n---------------------------------------------------------------------------" \
         << std::endl

#define LSPACE\
     LOUTCLEAN \
         << std::endl        

#ifndef DEBUG_ONLY_ERROR

#   define AVAR(var)                { DVAR(var)               ; LVAR(var)               ; } 
#   define AHEX(var)                { DHEX(var)               ; LHEX(var)               ; } 
#   define AMSG(var)                { DMSG(var)               ; LMSG(var)               ; }
#   define AERR(var)                { DERR(var)               ; LERR(var)               ; }
#   define AFUN                     { DFUN                    ; LFUN                    ; }
#   define ASPLIT                   { DSPLIT                  ; LSPLIT                  ; }
#   define ASPACE                   { DSPACE                  ; LSPACE                  ; }

#else

#   define AVAR(var)                {  } 
#   define AHEX(var)                {  } 
#   define AMSG(var)                {  }
#   define AERR(var)                { DERR(var)               ; LERR(var)               ; }
#   define AFUN                     {  }
#   define ASPLIT                   {  }
#   define ASPACE                   {  }

#endif // !DEBUG_ONLY_ERROR


#define APAUSE AMSG("Press any key for continue..."); std::cin.get(); std::cin.get()