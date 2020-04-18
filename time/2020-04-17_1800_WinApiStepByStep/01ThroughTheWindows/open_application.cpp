#include "windows.h"
//#include "Shellapi.h" // ShellExecute

void open_application()
{
    ShellExecute(0, L"Open", L"mailto: tt@tts", L"", L"", 1);
}
