#include "windows.h"
#include <iostream>

using namespace std;

void find_calculator()
{
    HWND hwnd;
    hwnd = FindWindow(NULL, L"Calculator");
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
        }
        else cout << " Error Loading Menu" << endl;
    }
    else
    {
        cout << " Error Find Windows" << endl;
    }
}
