#pragma once

#include "SocketWrapperShared.h"

namespace StringUtils
{
	string GetCommandLineArg( int inIndex );

    std::wstring Sprintf( const WCHAR* inFormat, ... );

	void	Log( const WCHAR* inFormat );
	void	Log( const WCHAR* inFormat, ... );
}

#define LOG( ... ) StringUtils::Log( __VA_ARGS__ );