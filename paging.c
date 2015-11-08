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

//Increments age of all frame entries present
inline void agePlus(int num)
{
	int i;
	for(i=0;i<num;i++)
	{
		frames[i].age +=1;
	}
}

//Returns the index of the oldest frame
inline int findOldest(int num)
{
	int i;
	int oldestIndex;
	oldestIndex = 0;
	int age = 0;
	for(i=0;i<num;i++)
	{
		if(frames[i].age > age)
		{
			age = frames[i].age;
			oldestIndex = i;
		}
	}
	return oldestIndex;
}

int main (void)
{
	int i;
	int faultCounter = 1;
	int indexCounter = 0;
	bool frameFull = false;
	FILE *fp = fopen("file.txt","r");
	FILE *data = fopen("tmp.dat","w");
	int memRef = 0;
	
	if(!fp || !data)
	{
		 printf("FILE ERROR\n");
		 return -1;
	 }
	
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
		memRef++;
		if(memRef%1000 == 0)
		{
			fprintf(data,"%d %d\n",memRef,faultCounter);
		}
		if(pageTable[request].valid == false)
		{
			(frames[indexCounter]).pageNumber = request;
			(frames[indexCounter]).age = num - indexCounter;
			(pageTable[request]).frameNumber = indexCounter;
			(pageTable[request]).valid = true;
			if(indexCounter == num-1) break;
			faultCounter++;
			indexCounter++;
		}
		
		
	}
	
	//This is where the fun starts
	while(!feof(fp))
	{
		fscanf(fp,"%d",&request);
		//Increase age of entries with every memory reference
		agePlus(num);
		memRef++;
		//1. Assume all Frames occupied.
		//2. New Request?
		//3. Valid in page table?
		if(pageTable[request].valid == false)
		{
			
			faultCounter++;
			int old = findOldest(num);
			
		
			//1. Mark Page Swapped out as Invalid
			//2. Store new Page in Frame
			//3. Mark new Page as valid
			//4. update page table
			
			pageTable[frames[old].pageNumber].valid = false;
			frames[old].pageNumber = request;
			frames[old].age = 0;
			pageTable[request].frameNumber = old;
			pageTable[request].valid = true;
		}
		
		if(memRef%1000 == 0)
		{
			fprintf(data,"%d %d\n",memRef,faultCounter);
		}
	}
	
	printf("Page Faults: %d\n",faultCounter);
	
	fclose(fp);
	fclose(data);
	system("gnuplot -p -e \"plot 'tmp.dat' using 1:2 with lines\"");
	free(pageTable);
	free(frames);
}
	
