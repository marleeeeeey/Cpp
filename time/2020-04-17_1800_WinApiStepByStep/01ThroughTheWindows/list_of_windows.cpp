#include "windows.h"
#include <iostream>

using namespace std;

void list_of_windows()
{
    HWND hwnd;
    WCHAR windowName[MAX_PATH];
    hwnd = GetDesktopWindow();
    hwnd = GetWindow(hwnd, GW_CHILD);
    while (hwnd != 0)
    {
        hwnd = GetWindow(hwnd, GW_HWNDNEXT);
        GetWindowText(hwnd, windowName, 100);
        if (wcslen(windowName) > 0)
            std::wcout << windowName << std::endl;
    }
}
