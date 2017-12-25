#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char ** argv)
{
    std::cout << "Chrono_test: Hello" << std::endl;

    using namespace std::chrono_literals;

    auto t1 = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);

    std::chrono::duration<double, std::milli> e1 = t1-t2;
    std::chrono::duration<double, std::milli> e2 = t2-t1;
    std::cout << "e1 " << e1.count() << " ms\n";
    std::cout << "e2 " << e2.count() << " ms\n";

    bool is_less = e1 < std::chrono::duration<double>::zero();
    std::cout << "is_less " << is_less << std::endl;

    std::cout << "Chrono_test: GoodBye" << std::endl;
}
