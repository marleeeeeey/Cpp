#include <iostream>
#include "lib_a.h"
#include "lib_b.h"

int main()
{
    std::cout << "Hello from MAIN\n";
    std::cout << "superSum 10 and 5 = " << superSum(10, 5) << "\n";
    std::cout << "Get name from lib B: " << getLibBName() << "\n";
}
