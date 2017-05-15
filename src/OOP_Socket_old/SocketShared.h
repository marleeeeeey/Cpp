#pragma once

// #pragma comment(lib, "ws2_32.lib")
// #include <windows.h>
// #include <winsock.h>

// #define WIN32_LEAN_AND_MEAN
// #define NOMINMAX
// #include "Windows.h"
// #include "WinSock2.h"
// #include "Ws2tcpip.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

typedef int socklen_t;