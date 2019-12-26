#include "lib_a.h"
#include "secret_msg.h"
#include <iostream>
#include "private.hpp"

int superSum(int a, int b)
{
    std::cout << getSecretMsg() << std::endl;
    printPrivateHello();
    return a+b;
}
