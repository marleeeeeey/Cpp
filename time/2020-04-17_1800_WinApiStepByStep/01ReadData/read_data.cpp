#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;

void main()
{
	HANDLE hShared = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"WriteData");
	cout << "Wait !!!! Write File Data Proccess " << endl;
	WaitForSingleObject(hShared, INFINITE);
	ifstream ifs("C:\\bin\\write.txt");
	char buffer[100];
	ifs >> buffer;
	cout << "Read File Data  -  " << buffer << endl;
	CloseHandle(hShared);

	std::cin.get();
}