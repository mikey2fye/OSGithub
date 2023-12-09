#ifndef PROCESS_H
#define PROCESS_H

typedef struct Process { 
    int pid; // Process ID 
    int bt; // Burst Time 
    int art; // Arrival Time 
    int wt; // waiting time
    int tat; // turnaround time
    int pri; // priority
    int ct; //Completion time
}ProcessType; 

typedef int (*Comparer) (const void *a, const void *b);

#endif				// PROCESS_H