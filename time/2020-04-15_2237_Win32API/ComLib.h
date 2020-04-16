#pragma once

#include <Windows.h> // NULL

namespace ComLib
{
    void ShowFileOpenDialog();

    template <class T> void SafeRelease(T** ppT)
    {
        if (*ppT)
        {
            (*ppT)->Release();
            *ppT = NULL;
        }
    }
}

