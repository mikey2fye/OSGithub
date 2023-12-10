#ifndef PROCESS_H
#define PROCESS_H

#define P_SIZE 7		//size of the processes to read from file

/**
 * Abstraction of a process that needs to be sorted
 */
typedef struct _process {
	int pid;		/*Unique process identifier */
	int arrival_time;	/*higher the arrival_time value, later it occurs in timeline */
	int priority;		/*lower the priority number higher the priority */
} Process;

/**
 * Create a process
 * Pass in the process pointer that you want to be 
 * constructed with the pid, arrival time and priority
 */
void process_ctr(Process * p, int pid, int arrival_time, int priority);

#endif				// PROCESS_H
