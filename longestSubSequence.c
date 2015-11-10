#include <stdio.h>
#include <stdlib.h>
#define MAX(a,b) ((a>b)?(a):(b))


int findLCS(char *x,char *y,int m,int n)
{
	int L[m+1][n+1];
	int i,j;
	for(i=0;i<=m;i++)
	{
		L[i][0] = 0;
	}
	for(j=0;j<=n;j++)
	{
		L[0][j] = 0;
	}
	
	for(i=1;i<=m;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(x[i-1] == y[j-1])
			{
				L[i][j] = 1 + L[i-1][j-1];
			}
			else
			{
				L[i][j] = MAX(L[i-1][j],L[i][j-1]);
			}
		}
	}
	return L[m][n];
}


int main(void)
{
	char *x; //First string
	char *y; // Second String
	
	printf("Input String X: ");
	scanf("%ms",&x);
	printf("Input String Y: ");
	scanf("%ms",&y);
	int x_size = 0;
	int y_size = 0;
	
	while(x[x_size++] != '\0');
	x_size -=1;
	while(y[y_size++] != '\0');
	y_size -=1;
	
	int length = findLCS(x,y,x_size,y_size);
	
	printf("The Length of the Longest Common Subsequence is: %d\n",length);
	return 0;
	
}

