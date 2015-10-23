#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define NUM_PHILS 5

sem_t chopsticks[NUM_PHILS];
int state[NUM_PHILS]; //INIT to THINKING
sem_t mutex;

bool check(int num)
{
	if(num == 0)
	{
		sem_wait(&chopsticks[0]);
		sem_wait(&chopsticks[4]);
	}
	else
	{
		sem_wait(&chopsticks[num]);
		sem_wait(&chopsticks[num-1]);
	}
	
	return 1;
}

bool release(int num)
{
	if(num == 0)
	{
		sem_post(&chopsticks[0]);
		sem_post(&chopsticks[4]);
	}
	else
	{
		sem_post(&chopsticks[num]);
		sem_post(&chopsticks[num-1]);
	}
	return 1;
}

void* philosopher(void *i)
{
	int *n = i;
	int num = *n;
	while(1)
	{
		
		printf("Philosopher %d is HUNGRY\n",num+1);
		state[num] = HUNGRY;
		sem_wait(&mutex);
		if(state[num] == HUNGRY)
		{
			bool chops = check(num);
			if(chops)
			{
				state[num] = EATING;
			}
			printf("Philosopher %d is EATING\n",num+1);
		}
		
		state[num] = THINKING;
		release(num);
		printf("Philosopher %d is THINKING\n",num+1);
		sem_post(&mutex);
	}
			
	
	return NULL;
}

void *monitorMethod()
{
	void* status = NULL;
	pthread_t *phils;
	phils = malloc(sizeof(pthread_t)*NUM_PHILS);
	int i;
	sem_init(&mutex,0,1);
	
	for(i = 0; i<NUM_PHILS;i++)
	{
		printf("Philosopher %d is THINKING\n",i+1);
		state[i] = THINKING;
		pthread_create(&phils[i],NULL,philosopher,&i);
		
		sem_init(&chopsticks[i],0,1);
		
	}
	
	for(i=0;i<NUM_PHILS;i++)
	{
		pthread_join(phils[i],status);
	}
	
	return NULL;
}


int main(void)
{
	pthread_t thread;
	int i;
	void * status = NULL;
	
	pthread_create(&thread,NULL,monitorMethod,NULL); //create MONITOR
	pthread_join(thread,status); //WAIT FOR MONITOR TO FINISH

	for(i=0;i<NUM_PHILS;i++)
	printf("%d\n",state[i]);
	return 0;
}
