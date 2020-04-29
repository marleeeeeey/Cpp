#pragma once

#ifdef CROSSPLATFORMLIBRARY_EXPORTS
#define CROSSPLATFORMLIBRARY_API __declspec(dllexport)
#else
#define CROSSPLATFORMLIBRARY_API __declspec(dllimport)
#endif

typedef void(__stdcall* OnReceiveMessageCallBack)(const char*);

extern "C"
{
    void CROSSPLATFORMLIBRARY_API __stdcall SetReceiveMessageCallBack(OnReceiveMessageCallBack cb);
    void CROSSPLATFORMLIBRARY_API __stdcall StartCore();
    void CROSSPLATFORMLIBRARY_API __stdcall SendMsg(const char * msg);
}
