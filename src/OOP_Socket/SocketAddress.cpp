#include "RoboCatPCH.h"
#include "SocketAddress.h"


string	SocketAddress::ToString() const
{
	const sockaddr_in* s = GetAsSockAddrIn();
	char destinationBuffer[ 128 ];
	InetNtop( s->sin_family, const_cast< in_addr* >( &s->sin_addr ), destinationBuffer, sizeof( destinationBuffer ) );
	return StringUtils::Sprintf( "%s:%d",
								destinationBuffer,
								ntohs( s->sin_port ) );
}

