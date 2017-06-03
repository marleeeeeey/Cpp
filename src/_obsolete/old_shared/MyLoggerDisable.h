#pragma once

#include "StdInclude.h"
#include "HelperLib.h"

#define DEBUG_API inline

#ifdef QT_CORE_LIB

# include <MyQtLogger.h>

#endif // QT_CORE_LIB

inline string funSigPrepare(string fs) { return string(); }

#define FUNSIG funSigPrepare(__FUNCSIG__) 

inline std::ostream & voidOut()
{
    static std::ostream os(nullptr);
    return os;
}

DEBUG_API unsigned int _myDebugCounter() { return 0; }
DEBUG_API std::ostream & consoleOut(std::ostream * pCOUT = nullptr) { return voidOut(); }
DEBUG_API std::ostream & logOut(std::ostream * pCOUT = nullptr) { return voidOut(); }
DEBUG_API void russianConsole() { } 

DEBUG_API void keep_window_open() { }
DEBUG_API void keep_window_open(std::string s) { }

DEBUG_API void startProgram(std::string programName = PROJECT_NAME) { }
DEBUG_API void endProgram(bool isAutoOpenReport = true, 
                          string notepadPath = "Notepad++\\notepad++.exe", 
                          const int exitCode = 0) { }

DEBUG_API void error(const std::string & errormessage = "unknow exception") { }
DEBUG_API void warning(const std::string & warningMessage = "unknow warning") { }

DEBUG_API std::string dateStr() { return string(); }
DEBUG_API std::string timeStr() { return string(); }
DEBUG_API std::string dateTimeStr() { return string(); }


#define CODE_POS_OUT_SHORT      FUNSIG << "   "
#define CODE_POS_OUT            __FILE__ <<  "(" <<  __LINE__ <<  ")   " << CODE_POS_OUT_SHORT

#define DOUT      consoleOut() 
#define DVAR(var) DOUT
#define DHEX(var) DOUT
#define DMSG(var) DOUT
#define DERR(var) DOUT
#define DFUN      DOUT
#define DSPLIT    DOUT
#define DSPACE    DOUT

#define LOUTCLEAN logOut() 
#define LOUT      logOut() 
#define LVAR(var) LOUT
#define LHEX(var) LOUT
#define LMSG(var) LOUT
#define LERR(var) LOUT
#define LFUN      LOUT
#define LSPLIT    LOUT
#define LSPACE    LOUT  

#define AVAR(var) { } 
#define AHEX(var) { } 
#define AMSG(var) { }
#define AERR(var) { }
#define AFUN      { }
#define ASPLIT    { }
#define ASPACE    { }

