#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "> ";
char delimiters[] = " =\t\r\n";
extern char **environ;
bool is_background = false;
int child_terminated = 0;
int timer_set = 0;

void child_signal_handler(int signum) {
    int status;
    pid_t child_pid = waitpid(-1, &status, WNOHANG);
    while (child_pid > 0) {
        if (status == 0) {
            printf("Child process %d exited\n", child_pid);
        } else if (status > 0) {
            printf("Child process %d terminated by command\n", child_pid);
        }
        child_pid = waitpid(-1, &status, WNOHANG);
    }
    child_terminated = status;
}

void interrupt_signal_handler(int signum) {
    if (child_terminated == 0) {
        signal(SIGINT, interrupt_signal_handler);
        printf("\n");
        char current_directory[MAX_COMMAND_LINE_LEN];
        if (getcwd(current_directory, sizeof(current_directory)) != NULL) {
            printf("%s> ", current_directory);
        } else {
            fprintf(stderr, "getcwd error");
            printf("> ");
        }
        fflush(stdout);
        fflush(stderr);
    }
}

void alarm_signal_handler(int signum) {
    if (timer_set) {
        printf("\nTimer expired. Terminating process.\n");
        kill(0, SIGINT);
    }
}

void set_timer() {
    timer_set = 1;
    alarm(10);
}

void cancel_timer() {
    timer_set = 0;
    alarm(0);
}

void tokenize_command(char *command_line, char **arguments) {
    int i = 0;
    char *token = strtok(command_line, delimiters);

    while (token != NULL) {
        if (token[0] == '$') {
            char *var_name = token + 1;
            char *var_value = getenv(var_name);
            if (var_value != NULL) {
                arguments[i++] = var_value;
            } else {
                arguments[i++] = ""; // Set to an empty string if the variable is not found
            }
        } else {
            arguments[i++] = token;
        }
        token = strtok(NULL, delimiters);
    }

    arguments[i] = NULL; // Set the last element to NULL for execvp
}

void execute_external_command(char **arguments, bool is_background) {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        signal(SIGINT, SIG_DFL);
        // Execute the command
        execvp(arguments[0], arguments);
        perror("execvp");
        exit(EXIT_FAILURE); // Exit if execvp fails
    } else if (pid < 0) { // Error forking
        perror("fork");
    } else { // Parent process
        if (!is_background) {
            set_timer();
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
            }
            cancel_timer();
        }
    }
}

int main() {
    char command_line[MAX_COMMAND_LINE_LEN];
    char current_directory[MAX_COMMAND_LINE_LEN];
    char *arguments[MAX_COMMAND_LINE_ARGS];

    signal(SIGINT, interrupt_signal_handler);
    signal(SIGCHLD, child_signal_handler);
    signal(SIGALRM, alarm_signal_handler);

    while (true) {
        do {
            if (getcwd(current_directory, sizeof(current_directory)) != NULL) {
                printf("%s> ", current_directory);
            } else {
                fprintf(stderr, "getcwd error");
                printf("> ");
            }

            if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
                fprintf(stderr, "fgets error");
                exit(0);
            }
        } while (command_line[0] == 0x0A);

        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        tokenize_command(command_line, arguments);

        is_background = false;
        int i = 0;
        for (i; arguments[i] != NULL; i++) {
            if (strcmp(arguments[i], "&") == 0) {
                is_background = true;
                arguments[i] = NULL;
                break;
            }
        }

        // echo
        if (strcmp(arguments[0], "echo") == 0) {
            int i = 1;
            for (i; arguments[i] != NULL; i++) {
                char *arg = arguments[i];
                if (arg[0] == '$') {
                    char *var_name = arg + 1;
                    char *var_value = getenv(var_name);
                    if (var_value != NULL) {
                        printf("%s ", var_value);
                    }
                } else {
                    printf("%s ", arg);
                }
            }
            printf("\n");
        }
        // cd
        else if (strcmp(arguments[0], "cd") == 0) {
            if (arguments[1] != NULL) {
                if (chdir(arguments[1]) != 0) {
                    printf("%s not found.\n", arguments[1]);
                }
            }
        }
        // setenv
        else if (strcmp(arguments[0], "setenv") == 0) {
            if (arguments[1] != NULL && arguments[2] != NULL) {
                if (setenv(arguments[1], arguments[2], 1) != 0) {
                    perror("setenv");
                }
            } else {
                printf("Missing arguments.\nsetenv <variable>=<value>\n");
            }
        }
        // pwd
        else if (strcmp(arguments[0], "pwd") == 0) {
            printf("%s\n", current_directory);
        }
        // env
        else if (strcmp(arguments[0], "env") == 0) {
            if (arguments[1] != NULL) {
                char **env = environ;
                char *var_name = arguments[1];
                while (*env != NULL) {
                    if (strncmp(*env, var_name, strlen(var_name)) == 0 && (*env)[strlen(var_name)] == '=') {
                        printf("%s\n", *env);
                        break;
                    }
                    env++;
                }
                if (*env == NULL) {
                    printf("%s: not found\n", var_name);
                }
            } else {
                char **env = environ;
                while (*env != NULL) {
                    printf("%s\n", *env);
                    env++;
                }
            }
        }
        // clear
        else if (strcmp(arguments[0], "clear") == 0) {
            // Clear screen
            printf("\033[2J\033[H");
        }
        // exit
        else if (strcmp(arguments[0], "exit") == 0) {
            fflush(stdout);
            fflush(stderr);
            return 0;
        } else {
            // Execute external command
            execute_external_command(arguments, is_background);
        }
    }

    return -1;
}
