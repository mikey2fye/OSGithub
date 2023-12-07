/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int handled = 0; //global variable to keep track of signal handler
int running = 1;
int alarms = 0;

void handler(int signum)
{ 
    //signal handler
    printf("Hello World!\n");
	handled = 1; //exit after printing
}

void sig_handler(int signum) 
{
	printf("\nTotal alarms delivered: %d\n", alarms);
    printf("Program executed for %d seconds.\n", alarms);
	running = 0;
	exit(0);
}

int main(int argc, char * argv[])
{
    signal(SIGALRM,handler); //register handler to handle SIGALRM
	signal(SIGINT, sig_handler);

    while(running){
		alarm(1);
		pause();

		if (handled) {
			printf("Turing was right!\n");
			handled = 0;
			alarms++;
		}
	} //busy wait for signal to be delivered

    return 0; //if never reached
}