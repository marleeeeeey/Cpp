#include <string>
#pragma once


class ItemInterface
{
public:
    virtual ~ItemInterface() = default;
    virtual std::string toString() = 0;
};

typedef int(__cdecl* CreateModuleFunPtr)(void**);