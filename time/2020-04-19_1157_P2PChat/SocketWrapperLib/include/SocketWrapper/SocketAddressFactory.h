#pragma once

#include "RoboCatShared.h"

class SocketAddressFactory
{
public:

	static SocketAddressPtr CreateIPv4FromString( const string& inString );
};