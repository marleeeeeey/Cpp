#include "windows.h"
#include <iostream>

using namespace std;

void get_volume_info()
{
	WCHAR NameBuffer[MAX_PATH];
	WCHAR SysNameBuffer[MAX_PATH];
	DWORD VSNumber;
	DWORD MCLength;
	DWORD FileSF;

	if (GetVolumeInformation(L"C:\\", NameBuffer, sizeof(NameBuffer),
		&VSNumber, &MCLength, &FileSF, SysNameBuffer, sizeof(SysNameBuffer)))
	{
		wcout << NameBuffer << endl;
		wcout << SysNameBuffer << endl;
		wcout << VSNumber << endl;
	}
}