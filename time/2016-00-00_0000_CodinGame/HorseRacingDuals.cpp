#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main()
{
    int N;
    cin >> N; cin.ignore();
    set<int> strengths;
    
    for (int i = 0; i < N; i++) 
    {
        int Pi;
        cin >> Pi; cin.ignore();

        if (strengths.find(Pi) != strengths.end())
        {
            cout << 0 << endl;
            exit(1);
        }
        else
        {
            strengths.insert(Pi);
        }

        cerr << Pi << ", ";
    }

    auto it = strengths.begin();
    auto itEnd = strengths.end();

    int prevStrength;
    int minDiff;

    for (; it != itEnd; it++)
    {
        static int i = 0;

        if (i == 0)
        {
            //...
        }
        else if (i == 1)
        {
            minDiff = abs(prevStrength - *it);
        }
        else
        {
            int diff = abs(prevStrength - *it);

            if (diff < minDiff)
            {
                minDiff = diff;
            }

        }

        prevStrength = *it;
        i++;
    }

    cout << minDiff << endl;
}