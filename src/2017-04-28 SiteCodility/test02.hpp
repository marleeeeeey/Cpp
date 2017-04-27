#include "StdPlus/StdPlus.h"
using namespace std;

#include <vector>

int solution(vector<int>& A, int X) {
    int N = A.size();
    if (N == 0) {
        return -1;
    }
    int l = 0;
    int r = N - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (A[m] > X) {
            r = m - 1;
        }
        else {
            l = m;
        }
    }
    if (A[l] == X) {
        return l;
    }
    return -1;
}


int main()
{
//     std::vector<int> vars = { 1, 2, 2, 2, 3, 4 };
//     AVAR(solution(vars, 4));


//     std::vector<int> vars = { 1, 2, 5, 9, 9 };
//     AVAR(solution(vars, 5));

//     std::vector<int> vars = { 1, 2, 3, 4, 5, 6, 7, 8 };
//     AVAR(solution(vars, 2));

    std::vector<int> vars = { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 };
    AVAR(solution(vars, 9));

    APAUSE;
}