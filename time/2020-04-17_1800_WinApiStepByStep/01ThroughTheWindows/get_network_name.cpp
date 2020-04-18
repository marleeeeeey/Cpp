#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "mpr.lib")

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <Winnetwk.h>

void get_network_name()
{
    // doesn't work - ERROR_NOT_CONNECTED
    WCHAR inputValue[] = L"1234"; // Redirected-LocalDevice or Network-Resource-Remote-name

    DWORD dwRetVal;
    WCHAR UserName[MAX_PATH];
    DWORD dwNameLength = MAX_PATH;

    wprintf(L"Calling WNetGetUser with Network-Resource = %s\n", inputValue);

    dwRetVal = WNetGetUser(inputValue, UserName, &dwNameLength);

    if (dwRetVal == NO_ERROR) {

        wprintf(L"WNetGetUser returned success\n");
        wprintf(L"\tUsername=%s   NameLength=%d\n", &UserName, dwNameLength);
        exit(0);
    }

    else {
        wprintf(L"WNetGetUser failed with error: %u\n", dwRetVal);
        exit(1);
    }
}