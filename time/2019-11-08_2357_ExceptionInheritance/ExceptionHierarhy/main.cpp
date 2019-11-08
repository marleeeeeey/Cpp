#include <exception>
#include <iostream>

class MyException : public std::exception
{
    int a = 1000;

public:
    void sayHello() const
    {
        std::cout << "Hello " << a << std::endl;
    }
};

void foo()
{
    MyException e;

    try
    {
        throw e;
    }
    catch(const std::exception & e)
    {
        throw;
    }
    catch(...)
    {

    }
}

int main()
{
    std::cout << "Hello" << std::endl;

    try
    {
        foo();
    }
    catch(const MyException & e)
    {
        e.sayHello();
        std::cout << "GOOD" << std::endl;
    }
    catch(const std::exception & e)
    {
        std::cout << "BAD" << std::endl;
    }
}