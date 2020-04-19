#include <iostream>

#include "SocketWrapperLib/SocketWrapperShared.h"

const int GOOD_SEGMENT_SIZE = 100;

int main()
{
    SocketUtil::StaticInit();

    TCPSocketPtr listenSocket = SocketUtil::CreateTCPSocket(INET);
    SocketAddress receivingAddress(INADDR_ANY, 56790);
    int errBind = listenSocket->Bind(receivingAddress);
    if (errBind != NO_ERROR)
    {
        std::cout << ("Connection error during Bind. Error=" + std::to_string(-errBind));
        return 1;
    }
    std::cout << "Bind OK" << std::endl;
    std::cout << "Bind to: " << receivingAddress.ToString() << std::endl;


    int errListen = listenSocket->Listen();
    if (errListen != NO_ERROR)
    {
        std::cout << ("Connection error during Listen. Error=" + std::to_string(-errListen));
        return 1;
    }
    std::cout << "Listen OK" << std::endl;


    SocketAddress newClientAddress;
    auto clientSocket = listenSocket->Accept(newClientAddress);
    std::cout << "Accepted: " << newClientAddress.ToString() << std::endl;
    //clientSocket->SetNonBlockingMode(true);

    //clientSocket->SetNonBlockingMode(true); // TODO
    char segment[GOOD_SEGMENT_SIZE] = {};
    int bytesReceived = clientSocket->Receive(segment, GOOD_SEGMENT_SIZE);
    if (bytesReceived < 0)
    {
        std::cout << ("Connection error during SocketConnectionPoint::receive. Error=" + std::to_string(-bytesReceived));
        return 1;
    }
    std::cout << "Receive OK" << std::endl;
    std::cout << segment << std::endl;

    SocketUtil::CleanUp();
}