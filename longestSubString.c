/***************************************
 * Find the Longest Common Substring
 * in Two Given Strings X and Y using
 * DYNAMIC PROGRAMMING
 ***************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a,b) ((a>b)?(a):(b))
#define MIN(a,b) ((a<b)?(a):(b))


void findLCS(char *x,char *y,int m,int n)
{
	int L[m+1][n+1]; // Table for Dynamic Approach
	int i,j;
	int maxnum = 0;
	int row,col;
	for(i = 0;i <= m; i++)
	{
		for(j = 0;j <= n; j++)
		{
			if(i==0 || j==0) //Pad Outer Row/Col with 0
			{
				L[i][j] = 0;
			}
			else if(x[i-1] == y[j-1]) //If match increment value
			{
				L[i][j] = 1 + L[i-1][j-1];
				maxnum = MAX(L[i][j],maxnum); //SAVE max number
				row = i; //Save coordinates
				col = j;
			}
			else
			{
				L[i][j] = 0; //No match then 0
			}
		}
	}
	
	char buf[maxnum]; //buffer to store substring in reverse
	int size = 0;
	for(j=col-1;j>=col-maxnum;j--)
	{
		buf[size++] = y[j];
	}
	size = size-1;
	

	if(size > -1)
	{
		printf("\nThe Longest Common Substring is: ");
	
	for(i=size;i>=0;i--) //Print Substring in right Order
	{
		printf("%c",buf[i]);
	}
	printf("\n\n");
	}
	else
	printf("\nNo Common Substring\n\n");
	
}


int main(void)
{
	char *x; //First string
	char *y; // Second String
	
	printf("Input String X: ");
	scanf("%ms",&x); //Dynamic Allocation %ms on scanf
	printf("Input String Y: ");
	scanf("%ms",&y); //Dynamic Allocation %ms on scanf
	int x_size = 0;
	int y_size = 0;
	
	while(x[x_size++] != '\0'); //Find String Sizes
	x_size -=1;
	while(y[y_size++] != '\0');
	y_size -=1;
	
	
	findLCS(x,y,x_size,y_size);
	
	
	return 0;
	
}

