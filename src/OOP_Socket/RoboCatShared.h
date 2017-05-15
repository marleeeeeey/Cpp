#pragma once
#pragma comment(lib, "ws2_32.lib")


#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>


// #define WIN32_LEAN_AND_MEAN
// #define NOMINMAX
// 
// #include "Windows.h"
// #include "WinSock2.h"
// #include "Ws2tcpip.h"
typedef int socklen_t;


#include "memory"

#include "vector"
#include "unordered_map"
#include "string"
#include "list"
#include "queue"
#include "deque"
#include "unordered_set"
#include "cassert"

using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::queue;
using std::list;
using std::deque;
using std::unordered_map;
using std::string;
using std::unordered_set;

class RoboCat;
class GameObject;

#include "StringUtils.h"
#include "SocketAddress.h"
#include "SocketAddressFactory.h"
#include "UDPSocket.h"
#include "TCPSocket.h"
#include "SocketUtil.h"
