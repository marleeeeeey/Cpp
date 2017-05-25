#include "AllInclude.h"



int calculateVolume(const std::vector<int> & land) {

    int leftMax  = 0;
    int rightMax = 0;
    int left     = 0;
    int right    = land.size() - 1;
    int volume   = 0;

    while (left < right) 
    {

        if (land[left] > leftMax) 
            leftMax = land[left];


        if (land[right] > rightMax) 
            rightMax = land[right];


        if (leftMax >= rightMax)
        {
            volume += rightMax - land[right];
            right--;
        }
        else 
        {
            volume += leftMax - land[left];
            left++;
        }

    }
    return volume;
}

int main()
{
    AVAR(calculateVolume({ 2, 5, 1, 8, 3, 4, 7, 7, 6 }));
    AVAR(calculateVolume({ 2, 5, 1, 2, 3, 4, 7, 7, 6 }));
    AVAR(calculateVolume({ 2, 5, 1, 2, 3, 4, 7, 4, 6 }));
    APAUSE;
}