#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        printf("Child process (PID: %d)\n", getpid());
        exit(0);
    } else {
        // Parent process
        printf("Parent process (PID: %d) with child (PID: %d)\n", getpid(), child_pid);
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Child process exited with status: %d\n", exit_status);
        }
    }

    return 0;
}
