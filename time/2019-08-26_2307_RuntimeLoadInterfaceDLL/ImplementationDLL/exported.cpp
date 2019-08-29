#include "pch.h"
#include "exported.h"

class Car : public ItemInterface
{
public:
    std::string toString() override
    {
        return "Car";
    }
};

int createModule(ItemInterface** ptr)
{
    *ptr = new Car();
    return 0;
}
