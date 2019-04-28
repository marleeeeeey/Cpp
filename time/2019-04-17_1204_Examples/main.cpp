#include <stdexcept>
#include <iostream>

int main()
{
    try
    {
        throw std::logic_error("xxx");
    }
    catch(std::logic_error & e)
    {
        std::cout << e.what();
    }
}