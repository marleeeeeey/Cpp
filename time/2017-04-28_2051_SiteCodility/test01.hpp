#include "StdPlus/StdPlus.h"
using namespace std;

#include <vector>

int solution(int M, vector<int>& A) {
    int N = A.size();
    vector<int> count(M + 1, 0);
    int maxOccurence = 1;
    int index = 0;
    for (int i = 0; i < N; i++) {
        if (count[A[i]] > 0) {
            int tmp = count[A[i]];
            if (tmp > maxOccurence) {
                maxOccurence = tmp;
                index = i;
            }
            count[A[i]] = tmp + 1;
        }
        else {
            count[A[i]] = 1;            
        }
    }
    return A[index];
}


int main()
{
    AVAR(solution(3, std::vector<int> ({ 1, 2, 2, 2, 3, 4 })));

    APAUSE;
}