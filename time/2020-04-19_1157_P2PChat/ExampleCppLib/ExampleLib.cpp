
#include "ExampleLib.h"
#include <iostream>
#include <chrono>
#include <thread>

OnReceiveMessageCallBack gOnReceiveMsg = nullptr;
std::string gMsg = "Hello";
bool gStartFlag = true;

void __stdcall SetReceiveMessageCallBack(OnReceiveMessageCallBack cb)
{
    gOnReceiveMsg = cb;
}

void __stdcall StartCore()
{
    while (gStartFlag)
    {
        std::cout << gMsg << " ";
        if(gOnReceiveMsg)
        {
            gOnReceiveMsg(gMsg.c_str());
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(3s);
    }
}

void __stdcall SendMsg(const char* msg)
{
    gMsg = msg;
}
