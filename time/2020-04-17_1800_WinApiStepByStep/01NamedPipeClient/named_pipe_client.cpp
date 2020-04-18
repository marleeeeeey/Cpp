#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	HANDLE hp;
	hp = CreateFile(L"\\\\.\\pipe\\ipctest", GENERIC_READ,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hp != INVALID_HANDLE_VALUE)
	{
		cout << "Connected to pipe" << endl;
		int i;
		cin >> i;
	}
	else
	{
		cout << "Error pipe" << endl;
	}

	std::cin.get();
}