/*Given an integer array nums, find the sum of the elements between indices i and j (i <= j), inclusive.
The update(i, val) function modifies nums by updating the element at index i to val.
The insert(i, val) function insert val at index i
The delete(i) function delete val at index i

Example:
Given nums = [1, 3, 5, 7, 2, 4]
sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
delete(0)
sumRange(0, 2) -> 15
insert(0, 3)
sumRange(0, 2) -> 11

Note that: The worst-case time complexity of all operations should be better than O(n), where n is the total number of numbers. Please describe your algorithm and given the complexity analysis. Your codes should be written in C.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void sumRange(int *array, int *size);
void update(int *array, int *size);
void insert(int **array, int *size);
void delete(int **array, int *size);

int main(void)
{
	int size;
	int *array;
	int i;

	printf("Enter the Size of the Array: ");
	scanf("%d",&size);
	array = (int*)malloc(sizeof(int)*size);

	for(i=0;i<size;i++)
	{
		printf("Enter element %d: ",i);
		scanf("%d",&array[i]);
	}

	while(size > 0)
	{
		int choice;
		printf("Enter Choice -> \n");
		printf("1. sumRange(i,j)\n");
		printf("2. update(i,val)\n");
		printf("3. insert(i,val)\n");
		printf("4. delete(i)\n");
		printf("0. Exit\n");
		printf("Enter Choice: ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1: sumRange(array,&size);
					break;
			case 2: update(array,&size);
					break;
			case 3: insert(&array,&size);
					break;
			case 4: delete(&array,&size);
					break;
			case 0: free(array);
					return 0;
					break;
			default:
					break;

		}
	}


	return 0;
}

void sumRange(int *array,int *size)
{
	int i = -1;
	int j = -1;
	int sum = 0;
	while(i < 0 || (i>(*size)-1))
	{
		printf("Enter Starting Index: ");
		scanf("%d",&i);
	}
	while(j < 0 || (j>(*size)-1) || j<i)
	{
		printf("Enter the Ending Index: ");
		scanf("%d",&j);
	}


	for(;i<=j;i++)
	{
		sum += array[i];
	}

	printf("sumRange: %d\n",sum);
}

void update(int *array,int *size)
{
	int i = -1;
	int value;
	while(i<0 || (i>(*size)-1))
	{
		printf("Enter the Index To update: ");
		scanf("%d",&i);
	}
	printf("Enter the Value to be Updated: ");
	scanf("%d",&value);
	array[i] = value;
}

void insert(int **array,int *size)
{
	int i = -1;
	int value;
	while(i<0 || (i>(*size)-1))
	{
		printf("Enter the Insertion Index: ");
		scanf("%d",&i);
	}
	printf("Enter the Value to be Inserted: ");
	scanf("%d",&value);

	*size += 1;
	*array = (int *)realloc(*array,*size);
	
	int x;
	for(x = (*size)-2;x>=i;x--)
	{
		(*array)[x+1] = (*array)[x];
	}

	(*array)[i] = value;

}
void delete(int **array,int *size)
{
	int i = -1;
	while(i<0 || (i>(*size)-1))
	{
		printf("Enter the Index to be Deleted: ");
		scanf("%d",&i);
	}

	for(;i<(*size)-1;i++)
	{
		(*array)[i] = (*array)[i+1];
	}

	*size -=1;
	(*array) = (int*)realloc(*array,*size);
}
