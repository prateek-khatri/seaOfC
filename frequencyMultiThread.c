#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/******************************
Structure for storing words
received from each thread
******************************/
struct return_val{
	char wordlist[100][100];
	int count[100];
} *arr;

pthread_t *threads;
int lines;

/*****************************
Aggregates Frequency Sum of
different threads
*****************************/
int aggregate(char *a)
{
	int sum = 0;
	int i=0;

	while(1)
	{
		if(i==lines) break;
		int count = 0;
		while(1)
		{
			if(arr[i].count[count] == -1)
			{
				break;
			}
			
			
			if(strcmp(a,arr[i].wordlist[count]) == 0)
			{
				sum += arr[i].count[count];
				arr[i].count[count] = 0;
				
			}
			count++;
		}
		i++;
		
	}

				
	
	return sum;
}
	
/**************************
Function executed by each
thread on seperate line.
**************************/
void *word_count(void* num)
{ 
	
	int *ln = num;
	unsigned int line_number = *ln;
	line_number++;
	
	//printf("Thread %d\n",line_number);
	
	char cmd_p1[9] = "sed -n '\0";
	char cmd_p2[2];
	sprintf(cmd_p2,"%d",line_number);
	char cmd_p3[14] = "p' 'file.txt'\0";
	char command[100];
	command[0] = '\0';
	strcat(command,cmd_p1);
	strcat(command,cmd_p2);
	strcat(command,cmd_p3);
	//usleep(line_number);
	
	char cmd[100] = " | tr [:space:] '\\n' | grep -v '^\\s*$' | sort | uniq -c | sort\0";
	strcat(command,cmd);
	//printf("%s\n",command);
	//fflush(stdout);
	
	
	
	FILE *in;
	in= popen(command, "r");
	rewind(in);
	char buff[50];
	int counter = 0;
	while(fgets(buff,sizeof(buff),in))
	{
		char c=' ';
		int i = 0;
		int cnt = atoi(buff);
		arr[line_number-1].count[counter] = cnt;
		
		
		while(c!='\0')
		{
			c=buff[i];
			buff[i]=buff[i+6];
			i++;
		}
		
		int cnnt = 0;
		while(c!=' ')
		{
			c = buff[cnnt];
			cnnt++;
		}
		i=0;
		while(c!='\0')
		{
			c=buff[i];
			buff[i]=buff[i+cnnt];
			i++;
		}
		sprintf(arr[line_number-1].wordlist[counter],"%s",buff);
		//printf("%d %s",arr[line_number-1].count[counter],arr[line_number-1].wordlist[counter]);
		counter++;
	}
	arr[line_number-1].count[counter] = -1;
		
	
	fclose(in);
	
	  
	
	return NULL;
}

int main(void)
{
	
	FILE *fp;
	fp = fopen("file.txt","r");
	char a[200];
	lines = 0;
	void *status = NULL;
	
	
	while(fgets(a,sizeof(a),fp) !=NULL)
	{
		lines++;
	}
	fclose(fp);
	
	arr = (struct return_val*) calloc(lines, sizeof(struct return_val) * lines);
	threads = malloc(sizeof(pthread_t)*lines);

	
	int i;
	for(i=0;i<lines;i++)
	{		
			pthread_create(&threads[i],NULL,word_count,&i);
			pthread_join(threads[i],status);
	}
	free(threads);
	
	char final[65536][20];
	int final_cnt[65536] = {0};
	int final_ctr = 0;
	i = 0;
	//printf("ANSWER-------------\n");
	while(i!=lines)
	{
		
		int ctr = 0;
		while(arr[i].count[ctr] >= 0)
		{
			
			if(arr[i].count[ctr] > 0)
			{
				
				strcpy(final[final_ctr],arr[i].wordlist[ctr]);
				final_cnt[final_ctr] = arr[i].count[ctr];
				
				arr[i].count[ctr] = 0;
				int sum = aggregate(arr[i].wordlist[ctr]);
				final_cnt[final_ctr] += sum;
				printf("%d  %s",final_cnt[final_ctr],final[final_ctr]);
			}
			
			ctr++; final_ctr++;
		}
		i++; 
		if(i==lines)
		{
			break;
		}
	}
	
	
	
	free(arr);
	return 0;
}
	
