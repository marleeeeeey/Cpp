#include "StdPlus/StdPlus.h"

using namespace std;

int solution(vector< vector<int> > & table) 
{
    int rows = table.size();
    int cols = table.front().size();
    int count = 0;

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            count++;

            int cur = table[row][col];

            if (col > 0)
            {
                int left = table[row][col-1];

                if (cur == left)
                    count--;
            }

            if (row > 0)
            {
                int up = table[row-1][col];

                if (cur == up)
                    count--;
            }
        }
    }

    return count;
}

int main()
{
//     vector< vector<int> > table = 
//     {
//         { 5,4,4 },
//         { 4,3,4 },
//         { 3,2,4 },
//         { 2,2,2 },
//         { 3,3,4 },
//         { 1,4,4 },
//         { 4,1,1 },
//     };


    vector< vector<int> > table =
    {
        { 4, 4, 4 },
        { 4, 4, 4 },
        { 4, 4, 4 },
        { 4, 4, 4 },
        { 4, 4, 4 },
    };

    AVAR(solution(table));

    APAUSE;
}