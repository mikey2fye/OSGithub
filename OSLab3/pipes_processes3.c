#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    int pipeA[2], pipeB[2];
    pid_t childPid1, childPid2;

    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <argument>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipeA) == -1 || pipe(pipeB) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((childPid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (childPid1 == 0) {
        close(pipeA[0]);
        dup2(pipeA[1], STDOUT_FILENO);
        close(pipeA[1]);
        execlp("cat", "cat", "scores", NULL);
        perror("execlp cat");
        exit(EXIT_FAILURE);
    }

    if ((childPid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (childPid2 == 0) {
        close(pipeA[1]);
        dup2(pipeA[0], STDIN_FILENO);
        close(pipeA[0]);

        close(pipeB[0]);
        dup2(pipeB[1], STDOUT_FILENO);
        close(pipeB[1]);

        execlp("grep", "grep", argv[1], NULL);
        perror("execlp grep");
        exit(EXIT_FAILURE);
    }

    close(pipeA[0]);
    close(pipeA[1]);

    if ((childPid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (childPid1 == 0) {
        close(pipeB[1]);
        dup2(pipeB[0], STDIN_FILENO);
        close(pipeB[0]);
        execlp("sort", "sort", NULL);
        perror("execlp sort");
        exit(EXIT_FAILURE);
    }

    return 0;
}
