#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <time.h>
void processSystemCalls()
{
    int status;
    pid_t child_pid = fork();
    if (child_pid == 0)
    {
        printf("Child process (PID: %d) executing...\n", getpid());
        // Additional process-related system calls
        printf("Child process parent's PID: %d\n", getppid());
        printf("Child process real UID: %d\n", getuid());
        // Simulating a child process that does some work
        sleep(3);
        printf("Child process (PID: %d) exiting...\n", getpid());
        exit(42); // Exit with a custom status code
    }
    else if (child_pid > 0)
    {
        printf("Parent process (PID: %d) waiting for child (PID: %d) to finish...\n", getpid(),
               child_pid);
        wait(&status);
        printf("Child process (PID: %d) finished with exit status: %d\n", child_pid,
               WEXITSTATUS(status));
        // Additional process-related system calls for the parent process
        struct rusage usage;
        getrusage(RUSAGE_CHILDREN, &usage);
        printf("Parent process user CPU time used: %ld.%06ld seconds\n",
               usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
        printf("Parent process system CPU time used: %ld.%06ld seconds\n",
               usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
        struct tms time_info;
        times(&time_info);
        printf("Parent process user CPU time used (clock ticks): %ld\n",
               time_info.tms_utime);
        printf("Parent process system CPU time used (clock ticks): %ld\n",
               time_info.tms_stime);
    }
    else
    {
        perror("Fork failed");
    }
}

int main()
{
    int choice;
    do
    {
        printf("1. Process System Calls\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            processSystemCalls();
            break;
        case 2:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice. Please select a valid option.\n");
        }
    } while (1);
    return 0;
}