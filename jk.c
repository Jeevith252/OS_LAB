#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    // Fork a child process
    child_pid = fork();

    if (child_pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    if (child_pid == 0) {
        // Child process

        printf("Child Process: PID = %d\n", getpid());
                printf("\nWaiting for user to press Enter\n");
                printf("\nMeanwhile before pressing Enter\nOpen another terminal and run ps -a command\n");
        getchar();

        printf("Executing 'ls' command...\n\n");

        // Execute 'ls' command in the child process
        execl("/bin/ls", "ls", NULL);

        // This line is reached only if execl fails
        perror("execl");
        exit(1);
    } else {
        // Parent process

        printf("Parent Process: PID = %d\n", getpid());

        // Wait for the child process to finish
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("\nChild process exited with status %d\n", WEXITSTATUS(status));
        } else {
            fprintf(stderr, "Child process did not terminate normally\n");
        }

        printf("Parent process exits\n");
    }

    return 0;
}