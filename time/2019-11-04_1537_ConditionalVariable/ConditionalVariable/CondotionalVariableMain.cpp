#include <condition_variable>
#include <mutex>
#include <future>
#include <iostream>
#include <queue>
#include <numeric>
#include <chrono>
#include <thread>

namespace BookExample
{

bool readyFlag;
std::mutex readyMutex;
std::condition_variable readyCondVar;

void thread1()
{
    // do something thread2 needs as preparation
    std::cout << "<return>" << std::endl;
    std::cin.get();

    // signal that thread1 has prepared a condition
    {
        std::lock_guard<std::mutex> lg(readyMutex);
        readyFlag = true;
    } // release lock
    readyCondVar.notify_one();
}

void thread2()
{
    // wait until thread1 is ready (readyFlag is true)
    {
        std::unique_lock<std::mutex> ul(readyMutex);
        readyCondVar.wait(ul, [] { return readyFlag; });
    } // release lock

    // do whatever shall happen after thread1 has prepared things
    std::cout << "done" << std::endl;
}

int mainBook()
{
    auto f1 = std::async(std::launch::async, thread1);
    auto f2 = std::async(std::launch::async, thread2);
    return 0;
}

}

std::mutex g_inboxMutex;
std::condition_variable g_inboxCondVar;
std::queue<int> g_inbox;
std::vector<int> g_result;
bool is_close_application = false;
int g_notifyCount = 0;
int g_notifyCount2 = 0;

void sleep_for(int count_ms)
{
    using namespace std::chrono_literals;
    std::chrono::milliseconds ms(count_ms);
    std::this_thread::sleep_for(ms);    
}

void processItem(int var)
{
    g_result.push_back(var);
    int sum = std::accumulate(g_result.begin(), g_result.end(), 0);
    sleep_for(100);
    std::cout << "size=" << g_result.size() <<  "; var=" << var <<
        "; sum=" << sum << std::endl;
}

void processInbox()
{
    while(true)
    {
        int var;
        int restCount = 0;

        {
            std::unique_lock<std::mutex> inboxLock(g_inboxMutex);
            g_inboxCondVar.wait(inboxLock, []
            {
                g_notifyCount++;
                return !g_inbox.empty() || is_close_application;
            });
            g_notifyCount2++;

            if(is_close_application == true)
                break;

            var = g_inbox.front();
            g_inbox.pop();
            restCount = g_inbox.size();
        }

        processItem(var);
        std::cout << "restCount=" << restCount << 
            "; notifyCount=" << g_notifyCount <<
            "; notifyCount2=" << g_notifyCount2 <<
            std::endl;
    }
}

void listenInbox()
{
    while (true)
    {
        int countVariables = 0;
        std::cin >> countVariables;
        std::cout << "count variables is " << countVariables << std::endl;
        if(countVariables == 0)
        {
            is_close_application = true;
            g_inboxCondVar.notify_one();
            break;
        }
        std::unique_lock<std::mutex> inboxLock(g_inboxMutex);
        for(auto i = 0; i < countVariables; ++i)
        {
            g_inbox.push(i);
        }
        g_inboxCondVar.notify_one();
    }
}

int main()
{
    auto f1 = std::async(std::launch::async, processInbox);
    listenInbox();
}
