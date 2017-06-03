#ifndef StdHelper_h__
#define StdHelper_h__

#include "StdInclude.h"

typedef void(*CallbackVoid) (void *);

// ************************** OTHER ***************************************

inline bool file_exist(const std::string& name) 
{
    std::ifstream f(name.c_str());
    return f.good();
}

template<class T>
std::vector<T> to_vector(const T * begin, const size_t size)
{
    std::vector<T> vec;
    vec.assign(begin, begin + size);
    return vec;
}

inline void thread_sleep(unsigned time_ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time_ms));
}

inline char waitKeyboardKey()
{
    char val = _getch();
    val = tolower(val);

    return val;
}


template<typename T>
T getNormal_rad(T var)
{
    return var - ((2 * M_PI)*floor((var / (2 * M_PI))));
}


template<class T>
T getRandom(const T & min, const T & max)
{
    static bool isFirstRun = true;
    if (isFirstRun)
    {
        srand((unsigned)time(NULL));
        isFirstRun = false;
    }

    if (min == max)
        return min;

    unsigned xMax = RAND_MAX;

    T diff = max - min;

    if (diff < 0)
        throw(std::logic_error("Error random diff"));

    double k = (double)diff / xMax;
    double ret = k * rand() + min;

    return (T)ret;
}

inline void createFolder(const std::string & path)
{
    _mkdir(path.c_str());
}


// *********************** DATE TIME **************************************

inline std::string dateStr()
{
    time_t t = time(0);   // get time now
    tm timeInfo;
    localtime_s(&timeInfo, &t);

    enum { stringSize = 12 };
    char cString[stringSize];
    strftime(cString, stringSize, "%Y-%m-%d", &timeInfo);

    std::string retStr(cString);
    //retStr.push_back(' ');

    return retStr;
}

inline std::string timeStr()
{
    using std::setw;
    using std::setfill;

    SYSTEMTIME st;
    GetSystemTime(&st);

    std::ostringstream os;
    os
        << setw(2) << setfill('0') << st.wHour         << "-"
        << setw(2) << setfill('0') << st.wMinute       << "-"
        << setw(2) << setfill('0') << st.wSecond       << "-"
        << setw(3) << setfill('0') << st.wMilliseconds //<< " "
        ;

    return os.str();
}

inline std::string dateTimeStr()
{
    return dateStr() + " " + timeStr();
}



// *********************** TO std::string **************************************

// trim from left
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from right
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from left & right
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}


template<class T>
std::string to_string(const T& t)
{
    std::ostringstream os;
    os << t;
    return os.str();
}

template<class T>
std::string to_stringHex(const T& t)
{
	std::ostringstream os;
	os << std::hex << t;
	return os.str();
}

inline int to_int(const std::string & str)
{
    int val;
    std::istringstream ss(str);
    ss >> val;

    return val;
}

template<>
inline std::string to_string(const bool& t)
{
    if (t == true)
        return "true";

    return "false";
}

inline std::string removeFromString(
    const std::string & source, const std::string remString)
{
    std::size_t foundPos = source.find(remString);

    if (foundPos == std::string::npos)
        return source;

    std::string ret = source;
    ret.erase(foundPos, remString.length());
    return ret;
}


inline std::string removeFromString(const std::string source, 
	const std::initializer_list<const char *> & remStrings)
{
	std::string ret = source;

    for (auto & remStr : remStrings)
		ret = removeFromString(ret, to_string(remStr));

    return ret;
}


inline std::string removeFromString(const std::string source,
	const std::vector<std::string> & remStrings)
{
	std::string ret = source;

	for (auto & remStr : remStrings)
		ret = removeFromString(ret, to_string(remStr));

	return ret;
}


inline std::string funSigPrepare(std::string fs)
{
    return removeFromString(fs, 
    { "__thiscall ", "__cdecl " });
}

inline std::vector<std::string> split(const std::string &s, char delim) 
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;
    while (getline(ss, item, delim)) 
    {
        tokens.push_back(item);
    }
    return tokens;
}


inline std::vector<std::string> splitByLenght(std::string str, std::size_t line_sz)
{
    if (str.size() <= line_sz)
        return{ str };

    std::vector<std::string> result;

    for (int i = 0; i < str.size() - line_sz; i+=line_sz)
    {
        result.push_back(str.substr(i, line_sz));
    }

    return result;
}


inline std::string fileNamePrepare(std::string fileName)
{
    return split(fileName, '\\').back();
}


// ********************* PRINT FUNCTION ***********************************

inline unsigned int logCnt()
{
    enum 
    {
        e_begin = 100,
        e_end = 999,
    };

    static unsigned counter = e_begin;
    if (++counter >= e_end)
    {
        counter = e_begin;
    }

    return counter;
}

#define AFUNSIG       funSigPrepare(__FUNCSIG__) 
#define AFILENAME     fileNamePrepare(__FILE__) 
#define AFILELINE     to_string(__LINE__)
#define APOSFILE      (AFILENAME + "(" + AFILELINE + ")")
#define APAUSE        std::cout << logCnt() << " PAUSE (press any key for continue)"; std::cin.get()
#define AVAR(var)     std::cout << logCnt() << " VAR " << #var << "=" << to_string(var) << std::endl
#define AMSG(var)     std::cout << logCnt() << " MSG " <<  (var) << std::endl
#define AFUN          std::cout << logCnt() << " FUN " << AFUNSIG << std::endl
#define ASPLIT        std::cout << "-------------------------------------------------------------------------------------\n"
#define ASPACE        std::cout << "\n"
#define ABEEP         std::cout << '\a';


template<class T>
std::ostream & operator<<(std::ostream & os, const std::vector<T> & vec)
{
    os << " VECTOR_SIZE=" << vec.size() << ": ";

    if (vec.empty())
        return os;    

    int index = 0;
    for (const auto & el : vec)
    {
        os << std::endl;
        os << "Vector index [" << std::setw(2) << index  << "]" << std::endl;
        os << el;

        index++;
    }
    
    return os;
}


// ********************* EASY EXCEPTION AND ERROR *************************

#define ADEBUGMSG(var) "[ " + to_string(#var) + " ] in file " + APOSFILE + AFUNSIG

#define AEXCEPT_IF(var)  if(var) throwExcept(ADEBUGMSG(var))
#define AERR_IF(var)     if(var) throwError (ADEBUGMSG(var))

inline void throwExcept(const std::string & errormessage = "unknown")
{
    const std::string prefix = " EXCEPT: ";
    AMSG(prefix + errormessage);
    std::cerr << dateTimeStr() << prefix << errormessage << "\n" << std::endl;
    throw std::logic_error(errormessage);
}

inline void throwError(const std::string & errormessage = "unknown")
{
    const std::string prefix = " RT_ERROR: ";
    AMSG(prefix + errormessage);
    std::cerr << dateTimeStr() << prefix << errormessage << "\n" << std::endl;
}

#endif // StdHelper_h__
