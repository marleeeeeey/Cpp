#pragma once

#include "SocketShared.h"
#include <stdint.h>
#include <string>
#include <memory>

class SocketAddress
{
    friend class UDPSocket;
    friend class TCPSocket;

public:

    SocketAddress(uint32_t inAddress, uint16_t inPort);
    SocketAddress(const sockaddr& inSockAddr);
    SocketAddress();

    bool operator==(const SocketAddress& inOther) const;

    size_t GetHash() const;
    uint32_t GetSize() const;
    std::string ToString() const;

private:

    sockaddr mSockAddr;

    uint32_t& GetIP4Ref();
    const uint32_t& GetIP4Ref() const;
    
    sockaddr_in* GetAsSockAddrIn();
    const sockaddr_in* GetAsSockAddrIn() const;

};

typedef std::shared_ptr< SocketAddress > SocketAddressPtr;

namespace std
{
    template<> struct hash< SocketAddress >
    {
        size_t operator()(const SocketAddress& inAddress) const
        {
            return inAddress.GetHash();
        }
    };
}