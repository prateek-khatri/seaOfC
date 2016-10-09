#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LARGEST 2
#define MIDDLE 1
#define THIRD_LARGEST 0

inline
void insertLargest(int n, int * topThree)
{
    // Where n is greater than nums[2]
    topThree[THIRD_LARGEST] = topThree[MIDDLE];
    topThree[MIDDLE] = topThree[LARGEST];
    topThree[LARGEST] = n;
}

inline
void insertMiddle(int n, int * topThree)
{
    // Where n is greater than middle but smaller than largest
    topThree[THIRD_LARGEST] = topThree[MIDDLE];
    topThree[MIDDLE] = n;
}

inline
void insertSmallest(int n, int * topThree)
{
    // where n is the third largest
    topThree[THIRD_LARGEST] = n;
}

void placeNum(int n, int * topThree)
{
    if (n > topThree[LARGEST])
    {
        insertLargest(n, topThree);
    }
    else if (n > topThree[MIDDLE])
    {
        insertMiddle(n, topThree);
    }
    else if(n > topThree[THIRD_LARGEST])
    {
        insertSmallest(n, topThree);
    }
}

int thirdMax(int* nums, int numsSize) {
    
    if (numsSize < 3)
    {
        if (numsSize < 2) return nums[0];
        
        if (nums[0] > nums[1]) return nums[0];
        else return nums[1];
    }
    
    int topThree[3];
    
    int i;
    for (i = 0; i < numsSize; i++)
    {
        placeNum(nums[i], topThree);
    }
    
    return topThree[THIRD_LARGEST];
}

int main(void)
{
    int arr[] = {1,2,3,4,5,6};
    int numsSize = 6;

    printf("num: %d\n", thirdMax(arr, numsSize));

    return 0;
}
