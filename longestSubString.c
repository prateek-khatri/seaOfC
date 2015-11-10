/***************************************
 * Find the Longest Common Substring
 * in Two Given Strings X and Y using
 * DYNAMIC PROGRAMMING
 * This program is a trail to use
 * Longest Common Subsequence Table
 * to find the longest substring
 ***************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) ((a>b)?(a):(b))


void findLCS(char *x,char *y,int m,int n)
{
	int L[m+1][n+1]; // Table for Dynamic Approach
	int i,j;
	for(i=0;i<=m;i++) //Set first Row as 0
	{
		L[i][0] = 0;
	}
	for(j=0;j<=n;j++) //Set first Column as 0
	{
		L[0][j] = 0;
	}
	
	for(i=1;i<=m;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(x[i-1] == y[j-1]) 
			{	//If Match Add 1 to previous diagonal
				L[i][j] = 1 + L[i-1][j-1];
			}
			else
			{	//If no match look for max from top and left
				L[i][j] = MAX(L[i-1][j],L[i][j-1]);
			}
		}
	}
	//String to Store LCS
	char substr[L[m][n]];
	int substr_size = L[m][n] - 1;
	////////BACKTRACK TO FIND SUBSTRING///////////////////
	for(i=m;i>=0;i--)
	{
		for(j=n;j>0;j--)
		{
			if(L[i][j] > L[i][j-1])
			{
				substr[seq_size--] = y[j-1];
				i--;
			}
		}
	}
	printf("\nThe Longest Common Sub-String is: %s\n\n",substr);
	
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

