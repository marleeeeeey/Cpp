#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;

void main()
{
	HANDLE hShared = CreateMutex(NULL, TRUE, L"WriteData");
	ofstream ofs("C:\\bin\\write.txt");
	ofs << "TestDataWrite" << endl;
	ofs.close();
	int i;
	cout << "Press Key and Enter for access to file " << endl;
	cin >> i;
	ReleaseMutex(hShared);
	CloseHandle(hShared);

	std::cin.get();
}