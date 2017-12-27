#pragma once
#include "OneLogStream.h"
#include <stdexcept>

int main(int argv, char ** argc)
{
    std::ofstream outFile("test");

    OneLogStream & logStream = OneLogStream::instanse();

    OneLogStream::Ostreams ostrs = { &std::cout, &outFile };
    logStream.setOstreams(ostrs);

    logStream << "test";
    logStream << setw(10) << double(10.3453);
    logStream << "WWW";
    
    cin.get();

    return 0;
}