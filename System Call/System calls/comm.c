#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {
    // Pipe
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        // Child process
        close(pipe_fd[0]);  // Close the read end
        const char *message = "Hello, Pipe Communication!";
        write(pipe_fd[1], message, strlen(message) + 1);
        close(pipe_fd[1]);
        exit(0);
    } else {
        // Parent process
        close(pipe_fd[1]);  // Close the write end
        char message_buffer[100];
        read(pipe_fd[0], message_buffer, sizeof(message_buffer));
        printf("Received from pipe: %s\n", message_buffer);
        close(pipe_fd[0]);

        wait(NULL);
    }

    // FIFO (Named Pipe)
    const char *fifo_path = "myfifo";
    mkfifo(fifo_path, 0666);

    pid_t fifo_child_pid = fork();

    if (fifo_child_pid == -1) {
        perror("fork");
        return 1;
    } else if (fifo_child_pid == 0) {
        // Child process for FIFO
        int fifo_fd = open(fifo_path, O_WRONLY);
        const char *fifo_message = "Hello, FIFO Communication!";
        write(fifo_fd, fifo_message, strlen(fifo_message) + 1);
        close(fifo_fd);
        exit(0);
    } else {
        // Parent process for FIFO
        int fifo_fd = open(fifo_path, O_RDONLY);
        char fifo_message_buffer[100];
        read(fifo_fd, fifo_message_buffer, sizeof(fifo_message_buffer));
        printf("Received from FIFO: %s\n", fifo_message_buffer);
        close(fifo_fd);

        wait(NULL);
    }

    return 0;
}
