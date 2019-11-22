#include "Windows.h"
#include <ctime>

int main()
{
    if(false) // set true to hide console
    {
        HWND hwnd = GetConsoleWindow();
        ShowWindow(hwnd, SW_HIDE);        
    }

    srand(time(NULL));



    return 0;
}
