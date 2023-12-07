/* hello_signal.c */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int handled = 0; //variable to keep track of signal handler (global)

void handler(int signum)
{ 
    //signal handler
    printf("Hello World!\n");
    handled = 1; //exit after printing
}

int main(int argc, char * argv[])
{
  signal(SIGALRM, handler); //register handler to handle SIGALRM

  while(1){
		alarm(1);
		pause();

		if (handled) 
        {
			printf("Turing was right!\n");
			handled = 0;
		}
	} //busy wait for signal to be delivered

  return 0; //never reached
}