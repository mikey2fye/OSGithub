#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

#define   MAX_COUNT  200

void  ChildProcess(void);              /* child process prototype  */
void  ParentProcess(void);             /* parent process prototype */

void main(void)
{
    ParentProcess();
}

void ChildProcess(void)
{
	time_t t;
	srand(getpid());
	int num = rand() % 30 + 1;

	for (num; num >= 0; num--) {
		pid_t pid = getpid();
		printf("Child Pid: %d is going to sleep!\n", pid);
		sleep(rand() % 10 + 1);
		printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n", pid, getppid());
	}
}

void ParentProcess(void)
{
    pid_t pid1, pid2;
	int status;

	pidA = fork();
	if (pidA == 0) {
		ChildProcess();
	}
	else if (pidA > 0) {
		pidB = fork();

		if (pidB == 0) {
			ChildProcess();
		}
		else if (pidB > 0) {
			wait(&status);
			printf("Child Pid: %d has completed.\n", pidA);
			wait(&status);
			printf("Child Pid: %d has completed.\n", pidB);
		}
		else {
			printf("Child B could not be forked.");
		}
	}
	else {
		printf("Child A could not be forked.");
	}
}