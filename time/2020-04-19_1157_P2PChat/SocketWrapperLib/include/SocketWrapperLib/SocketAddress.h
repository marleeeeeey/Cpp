#pragma once
#include "SocketWrapperShared.h"

class SocketAddress
{
public:
    //SocketAddress(string ipv4str, uint16_t port);
    SocketAddress(uint32_t inAddress, uint16_t inPort);
    SocketAddress(const sockaddr& inSockAddr);
    SocketAddress();
    bool operator==(const SocketAddress& inOther) const;
    size_t GetHash() const;
    uint32_t GetSize() const;
    string ToString() const;

private:
    friend class UDPSocket;
    friend class TCPSocket;
    sockaddr mSockAddr;

#if _WIN32
    uint32_t& GetIP4Ref();
    const uint32_t& GetIP4Ref() const;
#else
 uint32_t&    GetIP4Ref()     { return GetAsSockAddrIn()->sin_addr.s_addr; }
 const uint32_t&   GetIP4Ref()   const { return GetAsSockAddrIn()->sin_addr.s_addr; }
#endif

    sockaddr_in* GetAsSockAddrIn();
    const sockaddr_in* GetAsSockAddrIn() const;
};

typedef shared_ptr<SocketAddress> SocketAddressPtr;

namespace std
{
    template <>
    struct hash<SocketAddress>
    {
        size_t operator()(const SocketAddress& inAddress) const
        {
            return inAddress.GetHash();
        }
    };
}
