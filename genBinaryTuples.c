#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //included for uint32_t

void bin_gen(int n)
{
	int row = 1<<n;   // essentially 2^n
	int arr[row][n];	// hold value for sequence
	uint32_t counter = 0;
	int j;
	
	for(counter=0;counter<row;counter++) 
	{
		uint32_t tmp = counter;
		for(j=n-1;j>=0;j--)
		{
			if((tmp & 1) == 1) //bitwise and to find 1 or 0
			{
				arr[counter][j] = 1;
			}
			else
			{
				arr[counter][j] = 0;
			}
			tmp = tmp >> 1;  //shift to next bit 
		}
	}
	
	for(counter = 0; counter<row;counter++) //print the sequence
	{
		for(j=0;j<n;j++)
		{
			printf("%d",arr[counter][j]);  //printing the binary tuples
		}
		printf("\n");
	}
	
}
