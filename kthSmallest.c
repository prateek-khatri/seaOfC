#include <stdio.h>
#include <stdlib.h>

int find_kth(int a[],int b[],int size_a,int size_b,int k)
{
	if(size_a > size_b) return find_kth(b,a,size_b,size_a,k);
	// make the smaller array as A
	if(size_a == 0 && size_b > 0) return b[k-1];
	// if one array is empty simply return kth index value
	if(k==1) return (a[0]<=b[0])? a[0]:b[0];
	// if k is the smallest element return smallest value
	int i = (size_a <= k/2)? size_a: k/2;
	int j = (size_b <= k/2)? size_b: k/2;
	//find the k/2 index in the array or the max length if less
	if(a[i-1] < b[j-1]) return find_kth(a+i,b,(size_a-i),j,(k-i));
	else return find_kth(a,b+j,i,(size_b-j),(k-j));
	//discard the side of both the arrays in which k cannot be present
}

void main(void)
{
	int a[100];
	int b[100];
	int size_a = 0;
	int size_b = 0;
	while(1)
	{
		int var = 0;
		printf("Enter Array A elements (end with -1)\n");
		scanf("%d",&var);
		
		if(var == -1) break;
		a[size_a++] = var;
	}
	
	while(1)
	{
		int var = 0;
		printf("Enter Array B elements (end with -1)\n");
		scanf("%d",&var);
		
		if(var == -1) break;
		b[size_b++] = var;
	}
	
	printf("ENTER THE VALUE FOR K\n");
	int k;
	scanf("%d",&k);
	
	int answer = find_kth(a,b,size_a,size_b,k);
	printf("The %dth smallest element is %d\n",k,answer);
}
		
