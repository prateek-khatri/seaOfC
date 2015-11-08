#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool gen_subsets(int arr[],int size,int halfsum)
{
	int rows =  1<<size;
	int sum = 0;
	int cnt,j;
	for(cnt=0;cnt<rows;cnt++)
	{
		for(j=0;j<size;j++)
		{
			if(cnt & (1<<j))
			{
				sum+=arr[j];
			}
		}
		if(sum==halfsum) return true;
		else sum = 0;
	}
	
	return false;
	
}

bool main()
{
	int arr[100];
	int size = 0;
	int var = 0;
	int sum=0;
	printf("Enter Array Elements (-1 to end)\n");
	while(1)
	{
		scanf("%d",&var);
		if(var == -1) break;
		sum+=var;
		arr[size] = var;
		size++;
	}
	
	if(sum%2 != 0)
	{
		printf("NOPE\n");
		return false;
	}
	
	if(gen_subsets(arr,size+1,sum/2))
	{
		printf("YEPP\n");
		return true;
	}
	else
	{
		printf("NOPE\n");
		return false;
	}
	
}

