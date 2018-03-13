#include "CarSimulator.h"
#include <sstream>

void parse_string(std::istream & is, std::ostream & os)
{
    char ch;
    CarSimulator car_simulator;
    os << car_simulator << std::endl;
    while (is.get(ch) && is.good())
    {
        if (ch == '\n')
            continue;

        CarCommand cmd = make_command(ch);
        car_simulator.set_command(cmd);
        os << car_simulator << std::endl;
    }
}

int main()
{
    parse_string(std::istringstream("LLBR"), std::cout);
    std::cin.get();
}
