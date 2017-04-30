#include <iostream>
#include <vector>
#include <algorithm>
#include <list>


int main()
{
    int n;
    std::cin >> n;

    typedef std::vector<int> Tasks;
    Tasks tasks;
    tasks.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        int taskNumber;
        std::cin >> taskNumber;
        tasks.push_back(taskNumber);
    }
    
    std::vector<Tasks> cycles;
    

    for (int i = 0; i < tasks.size(); ++i)
    {
        int curTask = tasks[i];

        bool isPushBack = false;

        for (auto & c : cycles)
        {
            if (c.back() == curTask - 1)
            {
                c.push_back(curTask);
                isPushBack = true;
                break;
            }
        }

        if (!isPushBack)
        {
            cycles.push_back({ curTask });
        }
    }

    std::cout << cycles.size() << std::endl;
}


int main_1()
{
    int n;
    std::cin >> n;

    std::list<int> tasks;

    for (int i = 0; i < n; ++i)
    {
        int taskNumber;
        std::cin >> taskNumber;
        tasks.push_back(taskNumber);
    }

    int searchTask = 1;
    int count = 1;
    int lastTask = tasks.size();

    typedef std::list<int>::iterator ItInt;

    ItInt it = std::find(tasks.begin(), tasks.end(), searchTask);

    std::vector<ItInt> removeItems;

    while (true)
    {
        if (it == tasks.end())
            break;

        removeItems.push_back(it);

        int nextTask = searchTask + 1;

        if (nextTask > lastTask)
            break;

        auto itNext = std::find(it, tasks.end(), nextTask);

        if (itNext == tasks.end())
        {
            for (auto & item : removeItems)
            {
                tasks.erase(item);
            }

            removeItems.clear();

            it = std::find(tasks.begin(), tasks.end(), nextTask);
            count++;
        }
        else
        {
            it = itNext;
        }

        searchTask = nextTask;
    }

    std::cout << count << std::endl;

    return 0;
}