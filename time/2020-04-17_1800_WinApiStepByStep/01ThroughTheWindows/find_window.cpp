#include "windows.h"
#include <iostream>

using namespace std;

void find_window()
{
    HWND hwnd;
    hwnd = FindWindow(L"Notepad++", NULL);
    if (hwnd != NULL)
    {
        cout << "Calculator found - " << endl;
        HMENU hMenu;
        hMenu = GetMenu(hwnd);
        if (hMenu != NULL)
        {
            int iCount;
            iCount = GetMenuItemCount(hMenu);
            cout << "Menu Item - " << iCount << endl;
            for(int i = 0; i < iCount; ++i)
            {
                MENUITEMINFO menuInfo{ 0 };
                menuInfo.cbSize = sizeof(MENUITEMINFO);
                menuInfo.fMask = MIIM_STRING;
                menuInfo.fType = MFT_STRING;
                GetMenuItemInfo(hMenu, i, TRUE, &menuInfo);
                menuInfo.cch = menuInfo.cch+1;
                WCHAR bufName[100] = { 0 };
                menuInfo.dwTypeData = bufName;
                GetMenuItemInfo(hMenu, i, TRUE, &menuInfo);
                wcout << i << ". " << "-" << bufName << endl;
            }
        }
        else cout << " Error Loading Menu" << endl;
    }
    else
    {
        cout << " Error Find Windows" << endl;
    }
}

void close_window()
{
    HWND hwnd;
    auto appName = L"Notepad++";
    hwnd = FindWindow(appName, NULL);
    if (hwnd != NULL)
    {
        wcout << appName << " found" << endl;
        bool isOK = PostMessage(hwnd, WM_QUIT, 0, 0);
        if(isOK)
        {
            wcout << appName << " closed" << endl;
        }
        else
        {
            wcout << "Error closing " << appName << ". GLE=" << GetLastError() << std::endl;
        }
    }
    else
    {
        wcout << " Error FindWindow " << appName << endl;
    }
}
