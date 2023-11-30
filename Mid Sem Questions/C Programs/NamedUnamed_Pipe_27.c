#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

void unnamedPipeDemo()
{
    int pipefd[2];
    char buffer[BUFFER_SIZE];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // Child process
        close(pipefd[1]); // Close the write end of the pipe

        ssize_t bytesRead;
        while ((bytesRead = read(pipefd[0], buffer, BUFFER_SIZE)) > 0)
        {
            write(STDOUT_FILENO, buffer, bytesRead);
        }

        close(pipefd[0]); // Close the read end of the pipe
    }
    else
    {
        // Parent process
        close(pipefd[0]); // Close the read end of the pipe

        const char *message = "Hello from the parent process!";
        write(pipefd[1], message, strlen(message));

        close(pipefd[1]); // Close the write end of the pipe
    }
}

void namedPipeDemo()
{
    const char *fifoFile = "/tmp/myfifo";
    mkfifo(fifoFile, 0666);

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        // Child process
        int fd = open(fifoFile, O_RDONLY);
        char buffer[BUFFER_SIZE];

        ssize_t bytesRead;
        while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0)
        {
            write(STDOUT_FILENO, buffer, bytesRead);
        }

        close(fd);
    }
    else
    {
        // Parent process
        int fd = open(fifoFile, O_WRONLY);

        const char *message = "Hello from the parent process!";
        write(fd, message, strlen(message));

        close(fd);
    }

    unlink(fifoFile); // Remove the named pipe
}

int main()
{
    int choice;

    printf("Choose a pipe method to demonstrate:\n");
    printf("1. Unnamed Pipe\n");
    printf("2. Named Pipe (FIFO)\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        unnamedPipeDemo();
        break;
    case 2:
        namedPipeDemo();
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }

    return 0;
}
