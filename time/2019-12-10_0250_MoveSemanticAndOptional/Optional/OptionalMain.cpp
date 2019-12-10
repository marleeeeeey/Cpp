#include <optional>
#include <iostream>

class State;

class State
{
    std::optional<State> m_value;

};

std::ostream& operator<<(std::ostream& os, const State& rhs)
{
    return os << "state";
}

int main()
{
    std::optional<State> a;
    std::optional<State> b;
    State c;
    a = std::move(c);
    std::cout << "a = " << a.value() << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cin.get();
}
