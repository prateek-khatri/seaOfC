#include <stdio.h>
#include <stdlib.h>

int find_min(int arr[],int left,int right)
{
	
	int mid = (left+right)/2;
	if(right-left == 1)
	{
		if(arr[left] <= arr[right]) return arr[left];
		else return arr[right];
	}
	if(left==right)
	{
		return arr[left];
	}
	int v2 = find_min(arr,mid,right);
	int v1 = find_min(arr,left,mid-1);
	
	
	if(v1<=v2) return v1;
	else return v2;
}

int main()
{
	int var = 0;
	int size = 0;
	int arr[100];
	printf("Enter Elements (-1 to end)\n");
	while(1)
	{
		scanf("%d",&var);
		if(var == -1)
		{
			break;
		}
		arr[size++] = var;
	}
	int min = find_min(arr,0,size-1);
	
	printf("Min value is: %d\n",min);
	return 0;
}
