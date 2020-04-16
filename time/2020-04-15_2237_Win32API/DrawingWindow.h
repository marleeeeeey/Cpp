#pragma once
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "BaseWindow.hpp"

class DrawingWindow : public BaseWindow<DrawingWindow>
{
    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    ID2D1SolidColorBrush* pBrush;
    D2D1_ELLIPSE ellipse;

    void    CalculateLayout();
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();

public:

    DrawingWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL) {}
    PCWSTR  ClassName() const { return L"Circle Window Class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};
