#include "SocketAddress.h"



bool SocketAddress::operator==(const SocketAddress& inOther) const
{
    return (mSockAddr.sa_family == AF_INET &&
        GetAsSockAddrIn()->sin_port == inOther.GetAsSockAddrIn()->sin_port) &&
        (GetIP4Ref() == inOther.GetIP4Ref());
}

SocketAddress::SocketAddress()
{
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetIP4Ref() = INADDR_ANY;
    GetAsSockAddrIn()->sin_port = 0;
}

SocketAddress::SocketAddress(const sockaddr& inSockAddr)
{
    memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
}

SocketAddress::SocketAddress(uint32_t inAddress, uint16_t inPort)
{
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetIP4Ref() = htonl(inAddress);
    GetAsSockAddrIn()->sin_port = htons(inPort);
}

size_t SocketAddress::GetHash() const
{
    return (GetIP4Ref()) |
        ((static_cast<uint32_t>(GetAsSockAddrIn()->sin_port)) << 13) |
        mSockAddr.sa_family;
}

uint32_t SocketAddress::GetSize() const
{
    return sizeof(sockaddr);
}

std::string SocketAddress::ToString() const
{
    // TODO
//         const sockaddr_in* s = GetAsSockAddrIn();
//         char destinationBuffer[128];
//         InetNtop(s->sin_family, const_cast<in_addr*>(&s->sin_addr), destinationBuffer, sizeof(destinationBuffer));
//         return StringUtils::Sprintf("%s:%d",
//             destinationBuffer,
//             ntohs(s->sin_port));
}

const uint32_t& SocketAddress::GetIP4Ref() const
{
    return *reinterpret_cast<const uint32_t*>(&GetAsSockAddrIn()->sin_addr.S_un.S_addr);
}

uint32_t& SocketAddress::GetIP4Ref()
{
    return *reinterpret_cast<uint32_t*>(&GetAsSockAddrIn()->sin_addr.S_un.S_addr);
}

const sockaddr_in* SocketAddress::GetAsSockAddrIn() const
{
    return reinterpret_cast<const sockaddr_in*>(&mSockAddr);
}

sockaddr_in* SocketAddress::GetAsSockAddrIn()
{
    return reinterpret_cast<sockaddr_in*>(&mSockAddr);
}
