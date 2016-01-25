#include<stdio.h>
#include<stdlib.h>

int * searchRange(int *nums,int numsSize,int target, int* returnSize)
{
	int *result = (int*) malloc(sizeof(int)* (*returnSize));
	result[0] = -1;
	result[1] = -1;
	
	if(numsSize ==0) return result;
	
	int index = bin_search(nums,0,numsSize-1,target);
	printf("Index: %d\n",index);
	
	//search start and end pos here;
	if(index == -1)
	{
		return result;
	}
	
	int start;
	int end;
	
	int i=index;
	while(i>=0 && nums[i] == target)
	{
		i--;
	}
	i=i+1;
	start = i;
	i=index;
	while(i<numsSize && nums[i] == target)
	{
		i++;
	}
	i=i-1;
	end = i;
	result[0] = start;
	result[1] = end;
	
	return result;
	
	
}

int bin_search(int* nums, int left, int right,int target)
{
	
	int mid = (left+right)/2;
	while(left <=right)
	{
		if(nums[mid] < target)
		{
			left= mid+1;
		}
		else if(nums[mid] == target)
		{
			return mid;
		}
		else
		{
			right = mid-1;
		}
		mid = (left+right)/2;
	}
	
	return -1;
}
void main(void)
{
	int array[2];
	//[5, 7, 7, 8, 8, 10]
	array[0] = 2;
	array[1] = 2;

	
	int numsSize = 2;
	int target = 2;
	
	int a = 2;
	int* returnSize = &a;
	int *result = searchRange(array, numsSize, target, returnSize);
	
	printf("%d  %d\n",result[0],result[1]);
	
}


