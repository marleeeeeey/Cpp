#include "MainWindow.h"
#include <cassert>
#include "ComLib.h"
#include "resource.h"

PCWSTR  MainWindow::ClassName() const { return L"Sample Window Class"; }

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    wchar_t msg[32];
    switch (uMsg)
    {
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_DRAW_MODE:
            swprintf_s(msg, L"ID_DRAW_MODE\n");
            OutputDebugString(msg);
            break;

        case ID_SELECT_MODE:
            swprintf_s(msg, L"ID_SELECT_MODE\n");
            OutputDebugString(msg);
            break;

        case ID_TOGGLE_MODE:
            swprintf_s(msg, L"ID_TOGGLE_MODE\n");
            OutputDebugString(msg);
            break;
        }
        return 0;

    case WM_SETCURSOR:
        if (LOWORD(lParam) == HTCLIENT)
        {
            swprintf_s(msg, L"WM_SETCURSOR\n");
            OutputDebugString(msg);
            auto hCursor = LoadCursor(NULL, IDC_ARROW);
            SetCursor(hCursor);
            return TRUE;
        }
        break;

    case WM_SYSKEYDOWN:
        swprintf_s(msg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_SYSCHAR:
        swprintf_s(msg, L"WM_SYSCHAR: %c\n", (wchar_t)wParam);
        OutputDebugString(msg);
        break;

    case WM_SYSKEYUP:
        swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_KEYDOWN:
        swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_KEYUP:
        swprintf_s(msg, L"WM_KEYUP: 0x%x\n", wParam);
        OutputDebugString(msg);
        break;

    case WM_CHAR:
        swprintf_s(msg, L"WM_CHAR: %c\n", (wchar_t)wParam);
        OutputDebugString(msg);
        break;

    case WM_LBUTTONDOWN:
        OnLeftMouseClick();
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(m_hwnd, &ps);
        return 0;
    }

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}

void MainWindow::OnLeftMouseClick()
{
    ComLib::ShowFileOpenDialog();
}
