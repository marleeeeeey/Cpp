#pragma once

#include <Windows.h> // NULL
#include <comdef.h>  // Declares _com_error


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

    inline void throw_if_fail(HRESULT hr)
    {
        if (FAILED(hr))
        {
            throw _com_error(hr);
        }
    }
}

