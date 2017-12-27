// does not match

#include <iostream>
#include <mutex>
#include <queue>
#include <iomanip>
#include <chrono>

std::mutex mut;
std::queue<char> data_queue;
std::condition_variable data_cond;

void process(char ch)
{
    static int num = 0;
    std::cout << std::setw(3) << num << "-" << ch << std::endl;
    num++;
}

bool more_data_to_prepare()
{
    return true;
}

char prepare_data()
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    static char ch = 'a';
    char cur_char = ch;
    ch++;
    if (ch == 'z')
    {
        ch = 'a';
    }
    return cur_char;
}

void data_preparation_thread()
{
    std::cout << "Hello from data_preparation_thread" << std::endl;

    while (more_data_to_prepare())
    {
        char data = prepare_data();
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
}

void data_processing_thread()
{
    std::cout << "Hello from data_processing_thread" << std::endl;

    while (true)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [] {return !data_queue.empty(); });
        char data = data_queue.front();
        data_queue.pop();
        process(data);
    }
}

int main()
{
    std::cout << "Hello from condition_varable programm" << std::endl;

    std::thread second_thread(data_processing_thread);
    second_thread.detach();

    data_preparation_thread();

    std::cin.get();
}