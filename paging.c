#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct pageTable
{
	int frameNumber;
	bool valid;
} *pageTable;

struct frames
{
	int pageNumber;
	int age;
} *frames;

inline void agePlus(int num)
{
	int i;
	for(i=0;i<num;i++)
	{
		frames[i].age +=1;
	}
}

int main (void)
{
	int i;
	int faultCounter = 0;
	int indexCounter = 0;
	bool frameFull = false;
	FILE *fp = fopen("file.txt","r");
	
	printf("Enter the Number of Pages: \n");
	int num;
	scanf("%d",&num);
	
	pageTable = malloc (sizeof(pageTable)*num);
	for(i=0;i<num;i++)
	{
		pageTable[i].frameNumber = -1;
		pageTable[i].valid = false;
	}
	
	printf("Enter the Number of Frames: \n");
	scanf("%d",&num);
	frames = malloc (sizeof(frames)*num);
	for(i=0;i<num;i++)
	{
		frames[i].pageNumber = -1;
		frames[i].age = 0;
	}
	
	int request;
	while(!feof(fp))
	{
		fscanf(fp,"%d",&request);
		
		(frames[indexCounter]).pageNumber = request;
		(frames[indexCounter]).age = num - indexCounter;
		(pageTable[request]).frameNumber = indexCounter;
		(pageTable[request]).valid = true;
		
		if(indexCounter == num-1) break;
		faultCounter++;
		indexCounter++;
		
	}
	
	
	fclose(fp);
	free(pageTable);
	free(frames);
}
	
