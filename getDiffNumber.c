/*
Given an array arr of n unique non-negative integers, how can you most efficiently find a non-negative integer that is not in the array?

Your solution should return such an integer or null if arr contains all possible integers.
Analyze the runtime and space complexity of your solution.
*/
#include <stdio.h>
#define INT_MAX 2147483647

int  gettingDiffNumber(int arr[], int n)
{     
      uint8_t hash[n+1] = {0};
      
      // CASE 0
     if (n == INT_MAX) return -1;
   
      // CASE 1: 
      for (uint32_t i = 0; i < n; i++)
      {
         if (arr[i] < n+1)
         {
            hash[arr[i]] = 1;
         }

      }
  
      for (uint32_t i = 0; i < n+1; i++)
      {
         if (hash[i] == 0)
         {
            return i;
         }
      }
      
      return -1;

}
