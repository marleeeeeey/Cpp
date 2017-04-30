#include "AllInclude.h"

#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
    int n;
    std::cin >> n;

    std::vector<int> tasks;

    for (int i = 0; i < n; ++i)
    {
        int taskNumber;
        std::cin >> taskNumber;
        tasks.push_back(taskNumber);
    }

    int searchTask = 1;
    int count = 1;

    auto it = std::find(tasks.begin(), tasks.end(), searchTask);
    

    while (true)
    {
        if (it == tasks.end())
            break;
        
        int nextTask = searchTask + 1;

        if (nextTask > tasks.size())
            break;

        auto itNext = std::find(it, tasks.end(), nextTask);

        if (itNext == tasks.end())
        {
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
}