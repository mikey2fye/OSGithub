#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd1[2];  // Used to store two ends of the first pipe (P1 to P2)
    int fd2[2];  // Used to store two ends of the second pipe (P2 to P1)

    char fixed_str[] = "howard.edu";
    char input_str[100];
    pid_t p;

    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    printf("P1: Enter a string to send to P2: ");
    scanf("%s", input_str);

    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "fork Failed");
        return 1;
    }

    // Parent process (P1)
    else if (p > 0)
    {
        close(fd1[0]); // Close reading end of the first pipe (P1 to P2)
        close(fd2[1]); // Close writing end of the second pipe (P2 to P1)

        // Write input string to P2 and close the writing end of the first pipe
        write(fd1[1], input_str, strlen(input_str) + 1);

        // Wait for P2 to send back the concatenated string
        char received_str1[100];
        read(fd2[0], received_str1, 100);

        char received_str2[100];
        read(fd2[0], received_str2, 100);

        // Concatenate the entire first concatenated string to the received string
        char final_str[200];
        strcpy(final_str, received_str1);
        strcat(final_str, received_str2);

        // Print the final concatenated string
        printf("P1: Final Concatenated string: %s\n", final_str);

        // Close both ends
        close(fd1[1]);
        close(fd2[0]);
    }

    // Child process (P2)
    else
    {
        close(fd1[1]); // Close writing end of the first pipe (P1 to P2)
        close(fd2[0]); // Close reading end of the second pipe (P2 to P1)

        // Read a string from P1 using the first pipe
        char received_str[100];
        read(fd1[0], received_str, 100);

        // Concatenate "howard.edu" to the received string
        int k = strlen(received_str);
        int i;
        for (i = 0; i < strlen(fixed_str); i++)
            received_str[k++] = fixed_str[i];

        received_str[k] = '\0';

        printf("P2: Received string: %s\n", received_str);
        write(fd2[1], received_str, strlen(received_str) + 1);

        // Prompt for a second input
        char input_str2[100];
        printf("P2: Enter a second string to send to P1: ");
        scanf("%s", input_str2);

        // Write the second input string back to P1 using the second pipe
        write(fd2[1], input_str2, strlen(input_str2) + 1);

        // Close both ends
        close(fd1[0]);
        close(fd2[1]);

        exit(0);
    }
}