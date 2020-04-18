#include <windows.h>
#include <iostream>

using namespace std;

void main()
{
	HANDLE hp;
	hp = CreateNamedPipe(L"\\\\.\\pipe\\ipctest", PIPE_ACCESS_OUTBOUND,
		PIPE_TYPE_BYTE | PIPE_NOWAIT, 1, 0, 0, NMPWAIT_USE_DEFAULT_WAIT, NULL);
	if (hp != INVALID_HANDLE_VALUE)
	{
		cout << "Pipe created" << endl;
		int i;
		cin >> i;
	}
	else
	{
		cout << "Error Create Name Pipe " << endl;
	}

	std::cin.get();
}