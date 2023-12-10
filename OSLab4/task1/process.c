#include "process.h"

void process_ctr(Process * p, int pid, int arrival_time, int priority)
{
	p->pid = pid;
	p->arrival_time = arrival_time;
	p->priority = priority;
}
