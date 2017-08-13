#include <my_math/my_math.h>
#include <iostream>


int main()
{
    std::cout << "one=" << my_math::one() << std::endl;
    std::cout << "two=" << my_math::two() << std::endl;
    std::cout << "sum(1, 3)=" << my_math::sum(1, 3) << std::endl;

    std::cin.get();

    return 0;
}