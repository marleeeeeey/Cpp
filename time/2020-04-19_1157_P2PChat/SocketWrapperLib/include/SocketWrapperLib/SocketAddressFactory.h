#pragma once
#include "SocketWrapperShared.h"

class SocketAddressFactory
{
public:

    static SocketAddressPtr CreateIPv4FromString(const string& inString);
};
