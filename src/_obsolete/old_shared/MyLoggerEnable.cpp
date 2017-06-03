#include <MyLoggerEnable.h>
#include <ctime>
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <clocale>
#include <Windows.h>

int & isStartProgramm()
{
    static int isStart = false;
    return isStart;
}

std::ostream & consoleOut(std::ostream * pCOUT /*= nullptr*/)
{
    if (!isStartProgramm())
        startProgram();

    static std::ostream *os = nullptr;
    if (os)
        return *os;

    if (!pCOUT)
        os = &std::cout;
    else
        os = pCOUT;

    return *os;
}

std::ostream & logOut(std::ostream * pCOUT /*= nullptr*/)
{
    if (!isStartProgramm())
        startProgram();

    static std::ostream *os = nullptr;
    if (os)
        return *os;

    if (!pCOUT)
        os = &std::cerr;
    else
        os = pCOUT;

    return *os;
}

void keep_window_open()
{
    std::cin.clear();
    std::cout << "Please enter a character to exit\n";
    char ch;
    std::cin >> ch;
    return;
}

void keep_window_open(std::string s)
{
    if (s.empty()) return;
    std::cin.clear();
    std::cin.ignore(120, '\n');
    for (;;) {
        std::cout << "Please enter " << s << " to exit\n";
        std::string ss;
        while (std::cin >> ss && ss != s)
            std::cout << "Please enter " << s << " to exit\n";
        return;
    }
}

std::string dateStr()
{
    time_t t = time(0);   // get time now
    tm timeInfo;
    localtime_s(&timeInfo, &t);

    enum { stringSize = 12 };
    char cString[stringSize];
    strftime(cString, stringSize, "%Y-%m-%d", &timeInfo);

    std::string retStr(cString);
    retStr.push_back(' ');

    return retStr;
}

std::string timeStr()
{
	SYSTEMTIME st;
	GetSystemTime(&st);

	ostringstream os;
	os
		<< setw(2) << setfill('0') << st.wHour << ":"
		<< setw(2) << setfill('0') << st.wMinute << ":"
		<< setw(2) << setfill('0') << st.wSecond << ":"
		<< setw(3) << setfill('0') << st.wMilliseconds << " ";

	return os.str();
}

unsigned int _myDebugCounter()
{
    enum
    {
        e_startNumber = 100,
        e_endNumber = 990,
    };

    static int counter = e_startNumber;
    if (counter > e_endNumber)
        counter = e_startNumber;

    counter++;

    return counter;
}

string getLogFileName(string programName = "")
{
    static std::string logFileName;

    if (!logFileName.empty())
        return logFileName;

    if (programName.empty())
        programName = "Empty Program Name";

    logFileName = programName;

    if (logFileName.empty())
    {
        logFileName = "log ";
    }

    logFileName = dateTimeStr() + logFileName;
    logFileName += ".txt";

    replace_if(logFileName.begin(), logFileName.end(), [](const char &ch)
    { return ch == ':'; }, '_');

    return logFileName;
}

std::ofstream & onceLogFile()
{
    static std::ofstream ost;
    return ost;
}

void startProgram(std::string programName)
{
    isStartProgramm() = true;

    russianConsole();
    if (onceLogFile().is_open())
        onceLogFile().close();

    onceLogFile().open(getLogFileName(programName), std::ios_base::trunc);

    logOut(&onceLogFile());
    
    LOUTCLEAN
        << "* * * * * * * * * * * * * * * * * * * *" << "\n"
        << "*                                     *" << "\n"
        << "* module:      <MyLogger.dll>         *" << "\n"
        << "* developer:   Sergey Tyulenev        *" << "\n"
        << "* e-mail:      marleeeeeey@gmail.com  *" << "\n"
        << "* last update: 2017-01-06             *" << "\n"
        << "*                                     *" << "\n"
        << "* * * * * * * * * * * * * * * * * * * *" << "\n"
        << std::endl;
    
    LOUT
        // << dateStr()
        << "Programm " << programName << " started"
        << std::endl;
}

void error(const std::string & errormessage /*= "unknow exception"*/)
{
    AERR("EXCEPTION_ERROR: " + errormessage);
    throw std::runtime_error(errormessage);
}

std::string dateTimeStr()
{
    return dateStr() + timeStr();
}

void russianConsole()
{
//     // Работает только для потока вывода!
//     setlocale(LC_CTYPE, "rus");

    // Работает для двух потоков ввода/вывода!
    SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
}

void warning(const std::string & warningMessage /*= "unknow warning"*/)
{
    AERR(warningMessage);
}

void endProgram(bool isAutoOpenReport, string notepadPath, const int exitCode)
{
    LMSG("Exit program successful");

    if (isAutoOpenReport)
    {
        static std::vector<string> programFilesPaths 
        {
            "",
            "C:\\Program Files (x86)\\",
            "C:\\Program Files\\",
        };

        for (auto & path : programFilesPaths)
        {
            string cmdOpenReport = path + notepadPath + " " + getLogFileName();

            // блокирующий режим
            //system(cmdOpenReport.c_str());        

            // неблокирующий режим
            // If the function succeeds, the return value is greater than 31.
            unsigned result = WinExec(cmdOpenReport.c_str(), SW_SHOWNORMAL);      
            if (result > 31)
            {
                if (onceLogFile().is_open())
                {
                    onceLogFile().close();
                }
                break;
            }
        }
    }
    else
    {
        DMSG("Press ENTER for correct exit program");
        for (char ch; cin && cin.get(ch) && ch != '\n';);
        cin.clear();
        cin.get();
    }

    exit(exitCode);
}
