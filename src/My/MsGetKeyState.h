#pragma once
#include <windows.h>
#pragma comment(lib, "User32.lib")
#include <thread>
#include "StdHelper.hpp"

namespace MsGetKeyState
{
    bool isPlay = true;

    void threadKeyAnaliz()
    {
        enum 
        {
//             e_firstIndex = 65,
//             e_size = 'z' - 'a' + 1,
            e_firstIndex = 0,
            e_size = 255,
            e_lastIndex = e_firstIndex + e_size,                    
        };

        static bool prevCheckedKeys[e_size];
        memset(prevCheckedKeys, true, e_size);

        bool checkedKeys[e_size];
        memset(checkedKeys, false, e_size);
        
        while (isPlay)
        {
            for (int i = 0; i < e_size; ++i)
            {
                int b                = i + e_firstIndex;
                char ch              = char(b);
                const short keyState = GetKeyState(b);
                bool isChecked       = keyState & 0001; 
                checkedKeys[i]       = isChecked;

                if (prevCheckedKeys[i] != checkedKeys[i])
                {
                    LOUTCLEAN << ch;
                    cout << ch;
                    prevCheckedKeys[i] = checkedKeys[i];
                }
            }
        }
    }

    void threadKeyAnaliz2()
    {
        enum { e_size = 256 };

        char keys[e_size];

        while (true)
        {
            string s;

            for (int x = 0; x < e_size; x++)
            {
                s.push_back((char)(GetAsyncKeyState(x) >> 8));
            }

            AVAR(s);
        }

    }

    void resolve()
    {
        AFUN;
        
        std::thread(threadKeyAnaliz).detach();
        //std::thread(threadKeyAnaliz2).detach();

        std::cin.get();

    }
}