#define _AFXDLL
#include "afxwin.h" // CPen
#include <iostream>

using namespace std;

void draw_on_desktop()
{
    HWND hwnd;
    hwnd = GetDesktopWindow();
    HDC hdc;
    hdc = GetWindowDC(hwnd);
    int i;
    cin >> i;
    CPen pen(PS_SOLID, 4, RGB(255, 0, 0));
    SelectObject(hdc, pen);
    Ellipse(hdc, 0, 0, 200, 200);
	cin >> i;
}

void draw_in_console()
{
	HWND hwnd;
	hwnd = FindWindow(L"ConsoleWindowClass", NULL);
	int i;
	cin >> i;
	if (hwnd != NULL)
	{
		HDC hdc;
		hdc = GetWindowDC(hwnd);
		if (hdc != 0)
		{
			CPen pen(PS_SOLID, 4, RGB(255, 0, 0));
			SelectObject(hdc, pen);
			Ellipse(hdc, 90, 90, 120, 120);
			int i;
			cin >> i;
		}
		else cout << "Error DC Window" << endl;
	}
	else cout << "Error Find Window" << endl;
}