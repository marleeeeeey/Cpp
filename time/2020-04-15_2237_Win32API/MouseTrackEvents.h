#pragma once

#include <d2d1.h>
#pragma comment(lib, "d2d1")

class MouseTrackEvents
{
    bool m_bMouseTracking;

public:
    MouseTrackEvents();
    void OnMouseMove(HWND hwnd);
    void Reset(HWND hwnd);
};
