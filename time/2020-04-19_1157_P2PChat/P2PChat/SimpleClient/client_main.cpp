#include <iostream>

#include "SocketWrapperLib/SocketWrapperShared.h"

const int GOOD_SEGMENT_SIZE = 100;

int main()
{
    SocketUtil::StaticInit();


    std::string rawAdress = "127.0.0.1:56790";
    SocketAddressPtr newClientAddress = SocketAddressFactory::CreateIPv4FromString(rawAdress);
    std::cout << "Connecting to (raw): " << rawAdress << std::endl;
    std::cout << "Connecting to (converted): " << newClientAddress->ToString() << std::endl;
    if (!newClientAddress)
    {
        std::cout << ("Error during CreateIPv4FromString. Error=");
        return 1;
    }


    auto clientSocket = SocketUtil::CreateTCPSocket(INET);
    auto connectResult = clientSocket->Connect(*newClientAddress);
    if(connectResult < 0)
    {
        std::cout << "Error during Connect. Error=" << -connectResult;
        return 1;        
    }
    //clientSocket->SetNonBlockingMode(true);
    std::cout << "Press any key to send data";
    std::cin.get();

    std::string msg = "Hello";
    msg.resize(GOOD_SEGMENT_SIZE - 1);
    msg += '\0';
    const char* segment = msg.c_str();
    int bytesSent = clientSocket->Send(segment, GOOD_SEGMENT_SIZE);
    if (bytesSent < 0)
    {
        std::cout << ("Connection error during SocketConnectionPoint::send. Error=" + std::to_string(-bytesSent));
        return 1;
    }

    std::cout << "No Errors";
    std::cin.get();


    SocketUtil::CleanUp();
    
}