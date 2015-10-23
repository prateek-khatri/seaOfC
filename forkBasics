#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

void childProcess(void)
{
	pid_t pid = getpid();
	printf("Child Process ID = %d\n",pid);
}
void parentProcess(void)
{

	pid_t pid = getpid();
	printf("Parent Process ID = %d\n",pid);
}

void main(void)
{
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		childProcess();
	}
	else
	{
		parentProcess();
	}
}
