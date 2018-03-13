#include <iostream>
#include <map>

enum class CarDirection
{
    N, W, S, E, last_direction = E, first_direction = N,
};

enum class CarCommand
{
    left, right, beep,
};

enum class CarOption
{
    none, beep,
};

CarCommand make_command(const char & rcmd);

class CarSimulator
{
    friend std::ostream & operator<<(std::ostream & os, const CarSimulator & car);

public:
    void set_command(CarCommand& cmd);

private:
    CarDirection m_direction = CarDirection::N;
    CarOption m_car_option = CarOption::none;
};
