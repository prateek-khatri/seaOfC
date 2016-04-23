#include <stdio.h>
#include <stdlib.h>


int findDuplicate(const int* array,int size)
{
  int sum=0;
  for(int i=1;i<size;i++)
  {
    sum ^=i;
  }
  for(int i=0;i<size;i++)
  {
    sum ^= array[i];
  }
  
  return sum;
}

int main()
{
  int size;
  scanf("Enter Array Size: %d",&size);
  const int *array = (int*)malloc(sizeof(int)*size);
  printf("Enter Elements...\n");
  for(int i=0;i<size;i++)
  {
    scanf("%d",&array[i]);
  }
  
  int duplicate = findDuplicate(array,size);
  free(array);
  printf("Duplicate Element is: %d\n",duplicate);
}
