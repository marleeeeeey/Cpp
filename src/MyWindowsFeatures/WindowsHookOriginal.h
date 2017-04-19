#pragma once
#define _WIN32_WINNT 0x500
#include <windows.h>
#include <tchar.h>

namespace WindowsHookOriginal
{
    HHOOK	g_hHook;
    HANDLE  g_hEvent;
    UINT	g_uKey = VK_CAPITAL;
    UINT    g_uDisableKey = VK_LMENU;

    LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
    {
        AFUN;

        if (nCode == HC_ACTION)
        {
            KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT*)lParam;
            if (ks->vkCode == g_uKey && !(GetKeyState(g_uDisableKey) & 0x8000))
            {
                if (wParam == WM_KEYDOWN)
                {
                    HWND hWnd = GetForegroundWindow();
                    AttachThreadInput(GetCurrentThreadId(), GetWindowThreadProcessId(hWnd, NULL), TRUE);
                    HWND hWnd_thread = GetFocus();
                    if (hWnd_thread)
                        hWnd = hWnd_thread;

                    if (hWnd)
                        PostMessage(hWnd, WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)HKL_NEXT);
                }
                return 1;
            }
        }
        return CallNextHookEx(g_hHook, nCode, wParam, lParam);
    }

    void failed(const TCHAR *msg)
    {
        MessageBox(NULL, msg, _T("Error"), MB_OK | MB_ICONERROR);
        ExitProcess(1);
    }

    void CALLBACK TimerCallback(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
    {
        if (WaitForSingleObject(g_hEvent, 0) == WAIT_OBJECT_0)
            PostQuitMessage(0);
    }

    void resolve(int argc, wchar_t **argv)
    {
        MSG msg;

        argv = CommandLineToArgvW(GetCommandLineW(), &argc);
        if (argv != NULL && argc >= 2)
        {
            UINT uCmdKey = _wtoi(argv[1]);
            if (uCmdKey >= 0x01 && uCmdKey <= 0xFE)
                g_uKey = uCmdKey;

            if (argc >= 3)
            {
                UINT uDisableKey = _wtoi(argv[2]);
                if (uDisableKey >= 0x01 && uDisableKey <= 0xFE)
                    g_uDisableKey = uDisableKey;
            }
        }
        LocalFree(argv);

        g_hEvent = CreateEvent(NULL, TRUE, FALSE, _T("HaaliLSwitch"));
        if (g_hEvent == NULL)
            failed(_T("CreateEvent()"));

        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            failed(_T("LSwitch is already running!"));
        }

        if (SetTimer(NULL, 0, 500, TimerCallback) == 0)
            failed(_T("SetTimer()"));

        g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, GetModuleHandle(0), 0);
        if (!g_hHook)
            failed(_T("SetWindowsHookEx()"));

        while (GetMessage(&msg, 0, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        UnhookWindowsHookEx(g_hHook);
        CloseHandle(g_hEvent);
        ExitProcess(0);
    }

}
