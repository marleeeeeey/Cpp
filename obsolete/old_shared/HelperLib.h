#pragma once

#ifndef HELPERLIB_EXPORT
#    pragma comment(lib, "HelperLib.lib")
#endif 

#include <StdInclude.h>


#if !defined PROJECT_NAME
#define PROJECT_NAME "NoName"
#endif


// ****************************** SHARED DATA ************************************

class HelperLibData
{
public:
    bool   m_isPrintLine     = false;
    bool   m_isPrintBrackets = false;
    string m_separator       = ". ";
    string m_pairSeparator   = " | ";
    int    m_keyPlace        = 5;

    static inline HelperLibData & instance()
    {
        static HelperLibData data;
        return data;
    }

private:
    HelperLibData() {}
    HelperLibData(const HelperLibData & other) = delete;
    HelperLibData & operator=(const HelperLibData & other) = delete;
};


// ******************************** MATH *****************************************

template<typename T, int powerOfTen = 1000>
T roundPow(const T & value)
{
	return round(value * powerOfTen) / powerOfTen;
}


template <typename T> 
T radFromDeg(T angle_deg) 
{ 
	return angle_deg * static_cast<T>(M_PI) / 180; 
}

template <typename T> 
T degFromRad(T angle_rad) 
{ 
	return angle_rad * 180 / static_cast<T>(M_PI); 
}


// ******************************** SIZE OF **************************************


#define SIZEOF_ARR(var) (sizeof(var)/sizeof(*var))

template<typename T>
size_t sizeof_bit(const T * var, unsigned countVars = 1)
{
    return sizeof(*var) * 8 * countVars;
}



// ************************** DATA PRINT *****************************************


template<class T>
std::vector<T> to_vector(const T * begin, const size_t size)
{
    std:: vector<T> vec;
    vec.assign(begin, begin + size);
    return vec;
}


template<class T>
std::string to_string(const T& t)
{
    std::ostringstream os;
    os << t;
    return os.str();
}


template<class T, int width = 5>
std::string to_stringw(const T& t)
{
	std::ostringstream os;
	os << setw(width) << t;
	return os.str();
}

template<class T, int prec = 3>
std::string to_stringp(const T& t)
{
	std::ostringstream os;
	os << std::setprecision(prec) << t;
	return os.str();
}


template<>
std::string to_string(const bool& t);


template<class T>
std::string to_stringHex(const T& t)
{
	std::ostringstream os;
	os << std::hex << t;
	return os.str();
}


template<class TKey, class TVal>
inline void printPair(std::ostream & os, const std::pair<TKey, TVal> & p)
{
    auto & oneData = HelperLibData::instance();

    if (!oneData.m_isPrintLine)
        os << setw(oneData.m_keyPlace);

    os
        << p.first
        << oneData.m_separator
        << p.second
        ;


    if (oneData.m_isPrintLine)
        os << oneData.m_pairSeparator;
}

template<class TKey, class TVal>
std::ostream & operator<<(std::ostream & os, const std::pair<TKey, TVal> & p)
{
    auto & o = HelperLibData::instance();

    if (o.m_isPrintBrackets)
    {
        os << "(";
        printPair(os, p);
        os << ") ";
    }
    else
    {
        printPair(os, p);
    }

    return os;
}

template<class T>
std::ostream & operator<<(std::ostream & os, const std::vector<T> & vec)
{
    auto & oneData = HelperLibData::instance();

    os << " VECTOR_SIZE=" << vec.size() << ": ";

    if (vec.empty())
        return os;

    if (!oneData.m_isPrintLine)
        os << endl;

    int index = 0;
    for (const auto & el : vec)
    {
        auto p = std::make_pair(index, el);

        os << p;

        if (!oneData.m_isPrintLine)
            os << std::endl;
        
        index++;
    }

    return os;
}

template<class TKey, class TVal>
std::ostream & operator<<(std::ostream & os, const std::map<TKey, TVal> & items)
{
    auto & oneData = oneHelperLibData();

    os << " MAP_SIZE=" << items.size() << ": ";

    if (items.empty())
        return os;

    if (!oneData.m_isPrintLine)
        os << endl;
    
    for (const auto & el : items)
    {
        os << el;

        if (!oneData.m_isPrintLine)
            os << std::endl;
    }

    return os;
}

inline std::ostream & operator<<(std::ostream & os, const HelperLibData & data)
{
    os
        << "m_isPrintLine"     << "=" << to_string(data.m_isPrintLine)     << "; "
        << "m_isPrintBrackets" << "=" << to_string(data.m_isPrintBrackets) << "; "
        << "m_separator"       << "=" << to_string(data.m_separator)       << "; "
        ;

    return os;
}


// **************************** RANDOM *******************************************



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

template<typename T>
std::vector<T> getRandomVector(T expectedValue, size_t size, T neighboursDiff)
{
    std::vector<T> data;
    for (size_t i = 0; i < size; ++i)
    {
        T curStep = getRandom<T>(-neighboursDiff, neighboursDiff);
        
        data.push_back(expectedValue);

        expectedValue += curStep;
    }

    return data;
}

bool isProbability(float p);



// ************************ STRING ACTIONS ***************************************



std::string removeFromString(const std::string & sourse, std::string remString);

template<class T>
inline unsigned maxLength(map<T, string> container)
{
	unsigned maxLen = 0;

	for (auto & c : container)
	{
		unsigned len = c.second.length();
		if (len > maxLen) maxLen = len;
	}

	return maxLen;
}

template<typename T>
void fillDataOfString(T * data, size_t sizeData, string strData)
{
    const int countChars = sizeData * sizeof(T) / sizeof(char); 
    strData.resize(countChars, ' ');

    char * str = (char *)data;
    for (int i = 0; i < countChars; ++i)
    {
        str[i] = strData[i];
    }
}

template<typename T>
string getStringFromData(const T * data, size_t sizeData)
{
    const int countChars = sizeData * sizeof(T) / sizeof(char);

    string retStr;

    char * str = (char *)data;
    for (int i = 0; i < countChars; ++i)
    {
        retStr.push_back(str[i]);
    }

    retStr.erase(retStr.find_last_not_of(" \n\r\t") + 1);

    return retStr;
}




// ****************************** OTHER ******************************************




template<typename BType, size_t e_size = 1>
class BSet
{
public:
    BSet(BType * ws)
        : m_words(ws)
    {
        m_countBits = sizeof_bit(m_words, e_size);
        m_wordSize_bit = sizeof_bit(m_words);
    }

    void print()
    {
        for (int i = 0; i < e_size; ++i)
        {
            //AHEX((unsigned)m_words[i])
        }
    }

    inline void setBit(unsigned numBit)
    {
        checkNumBit(numBit);
        curWord(numBit) |= bitMask(numBit);
    }

    inline void resetBit(unsigned numBit)
    {
        checkNumBit(numBit);
        curWord(numBit) &= ~bitMask(numBit);
    }

    inline void switchBit(unsigned numBit)
    {
        checkNumBit(numBit);
        curWord(numBit) ^= bitMask(numBit);
    }

    inline bool isBit(unsigned numBit)
    {
        checkNumBit(numBit);
        return curWord(numBit) & bitMask(numBit);
    }

private:
    inline void throwErrorBits() { throw(std::logic_error("error bits")); }
    inline void checkNumBit(unsigned numBit)
    {
        if (numBit < 0 || numBit >= m_countBits)
            throwErrorBits();
    }
    inline unsigned numWord(unsigned numBit) { return numBit / m_wordSize_bit; }
    inline BType & curWord(unsigned numBit) { return m_words[numWord(numBit)]; }
    inline size_t numBitInWord(unsigned numBit) { return numBit % m_wordSize_bit; }
    inline BType bitMask(unsigned numBit)
    {
        BType bm = 1;
        bm = bm << numBitInWord(numBit);
        return bm;
    }

    BType * m_words;
    size_t  m_countBits = -1;
    size_t  m_wordSize_bit = -1;
};


void thread_sleep(unsigned time_ms);

inline string compileTime() { return __TIME__; }

inline string compileDate() { return __DATE__; }

