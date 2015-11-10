/***************************************
 * Find the Longest Common Substring
 * in Two Given Strings X and Y using
 * DYNAMIC PROGRAMMING
 ***************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a,b) ((a>b)?(a):(b))


void findLCS(char *x,char *y,int m,int n)
{
	
	
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

