#pragma once
#include "BaseWindow.hpp"

class MainWindow : public BaseWindow<MainWindow>
{
public:
    PCWSTR  ClassName() const;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};
