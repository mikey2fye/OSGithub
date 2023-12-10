#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#include "util.h"
#include "list.h"

/**
 * Returns an array of process that are parsed from
 * the input file descriptor passed as argument
 * CAUTION: You need to free up the space that is allocated
 * by this function
 */
void parse_file(FILE * f, int input[][2], int *n, int *PARTITION_SIZE)
{
  
  // get the initial partition sizeof
  
  fscanf(f,"%d\n", PARTITION_SIZE);
  printf("PARTITION_SIZE = %d\n", *PARTITION_SIZE);
  
  while (!feof(f)) {
		fscanf(f, "%d %d\n", &input[*n][0], &input[*n][1]);
    /*
    if(input[*n][0] != -99999 && input[*n][0] > 0)
        printf("PID=%d ALLOCATE=%dbytes\n", input[*n][0], input[*n][1]);
    else if (input[*n][0] != -99999 && input[*n][0] < 0)
        printf("DEALLOCATED PROC = %d\n", abs(input[*n][0]));
    else
        printf("COALESCE\n");
    */
    *n += 1;
	}
}