#include "SocketAddress.h"

class UDPSocket
{
public:

	~UDPSocket();

	int Bind( const SocketAddress& inToAddress );
	int SendTo( const void* inToSend, int inLength, const SocketAddress& inToAddress );
	int ReceiveFrom( void* inToReceive, int inMaxLength, SocketAddress& outFromAddress );

	int SetNonBlockingMode( bool inShouldBeNonBlocking );

private:
	friend class SocketUtil;
	UDPSocket( SOCKET inSocket ) : mSocket( inSocket ) {}
	SOCKET mSocket;

};

typedef std::shared_ptr< UDPSocket >	UDPSocketPtr;