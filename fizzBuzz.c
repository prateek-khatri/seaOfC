#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MUL_THREE(_n) ((_n) % 3 == 0)
#define MUL_FIVE(_n) ((_n) % 5 == 0)
#define MUL_BOTH(_n) (MUL_THREE(_n) && MUL_FIVE(_n))

#define FIZZ_SIZE 4
#define BUZZ_SIZE 4
#define FIZZBUZZ_SIZE 8

#define FIZZ "Fizz"
#define BUZZ "Buzz"
#define FIZZBUZZ "FizzBuzz"

char * fizzBuzzCheck(int n)
{
    char * returnString = NULL;
    
    if (MUL_BOTH(n))
    {
        returnString = (char *) malloc(sizeof(char)*FIZZBUZZ_SIZE);
        strcpy(returnString, FIZZBUZZ);
    }
    else if (MUL_THREE(n))
    {
        returnString = (char *) malloc(sizeof(char)*FIZZ_SIZE);
        strcpy(returnString, FIZZ);       
    }
    else if (MUL_FIVE(n))
    {
        returnString = (char *) malloc(sizeof(char)*BUZZ_SIZE);
        strcpy(returnString, BUZZ); 
    }
    else
    {
    	char buf[5];
    	snprintf(buf,5,"%d",n);
        returnString = (char *) malloc(sizeof(char)*strlen(buf));
        strcpy(returnString, buf);
    }

    return returnString;
    
}

char ** fizzBuzz(int n)
{
	if (n < 1)
    {
        return NULL;
    }
    
    char ** returnArray  = (char **) malloc (sizeof(char*) * n);
    
    int i;
    for (i = 0; i < n; ++i)
    {
    	returnArray[i] = fizzBuzzCheck(i+1);
    }
    return returnArray;
}

void printArray(char ** returnArray, const int fizzNum)
{
	int i;
	for (i = 0; i < fizzNum; i++)
	{
		printf("%s\n",returnArray[i]);
		free(returnArray[i]);
	}
	free(returnArray);

}

int main(void)
{
	const int fizzNum = 150;
	char ** returnArray = fizzBuzz(fizzNum);
	printArray(returnArray, fizzNum);
	return 0;
}
