void swap(int *p,int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}
void find_permutations(int* nums, int size,int ***answer,int* returnSize,int begin,int end)
{
    if(begin == end) // Leaf Node Reached - Base Case
    {
        (*returnSize)++; //NEXT PERMUTATION COMPLETED
        *answer = (int**)realloc(*answer,sizeof(int*)*(*returnSize)); // ALLOCATE NEW LOCATION
        (*answer)[*returnSize-1] = (int*)malloc(sizeof(int)*(size)); // ALLOCATE SIZE TO FIT NUMBERS
        for(int i=0;i<size;i++)
        {
            //DEEP COPY NUMS INTO ANSWER AT THE CORRECT PERMUTATION LOCATION
            (*answer)[*returnSize-1][i] = nums[i];
        }
        return;
    }
    for(int i = begin; i<=end;i++)
    {
        swap(nums+begin,nums+i);
        find_permutations(nums,size,answer,returnSize,begin+1,end);
        swap(nums+begin,nums+i);
    }
}

//NUMS = array
//numsSize = size of array
// returnSize = number of permutations created.
int** permute(int* nums, int numsSize, int* returnSize) 
{
    *returnSize = 0;
    int **answer = (int**)malloc(sizeof(int*));
    find_permutations(nums,numsSize,&answer,returnSize,0,numsSize-1);
    
    return answer;
} 
