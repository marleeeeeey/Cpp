// test_app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

class Foo
{
public:
    static const int bar = 3;
};

// comment this string for succesfull build
static_assert(Foo::bar > 4, "Foo::bar is too small :(");

int main()
{
    return Foo::bar;
    assert(2 + 2 == 4);
    std::cout << "Execution continues past the first assert\n";
    assert(2 + 2 == 5);
    std::cout << "Execution continues past the second assert\n";
    std::cin.get();
}

