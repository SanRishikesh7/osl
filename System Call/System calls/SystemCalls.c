#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

void process_control_example() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return;
    } else if (child_pid == 0) {
        printf("Child process (PID: %d)\n", getpid());
        exit(0);
    } else {
        printf("Parent process (PID: %d) with child (PID: %d)\n", getpid(), child_pid);
        wait(NULL);
    }
}

void file_management_example() {
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }
    const char *message = "Hello, File Management!\n";
    write(fd, message, strlen(message));
    close(fd);

    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return;
    }
    char buffer[100];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read != -1) {
        buffer[bytes_read] = '\0';
        printf("Read from file: %s", buffer);
    }
    close(fd);
}

void communication_example() {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return;
    }

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return;
    } else if (child_pid == 0) {
        close(pipe_fd[0]);
        const char *message = "Hello, Pipe Communication!";
        write(pipe_fd[1], message, strlen(message) + 1);
        close(pipe_fd[1]);
        exit(0);
    } else {
        close(pipe_fd[1]);
        char message_buffer[100];
        read(pipe_fd[0], message_buffer, sizeof(message_buffer));
        printf("Received from pipe: %s\n", message_buffer);
        close(pipe_fd[0]);

        wait(NULL);
    }
}

void information_maintenance_example() {
    pid_t current_pid = getpid();
    printf("Current process PID: %d\n", current_pid);

    signal(SIGALRM, SIG_DFL); // Reset the signal handler
    unsigned int seconds = 5;
    alarm(seconds);

    printf("Waiting for %d seconds...\n", seconds);
    sleep(seconds);

    printf("Sleeping for 3 seconds...\n");
    sleep(3);
    printf("Awake now!\n");
}

int main() {
    int choice;

    do {
        printf("\nMenu:\n");
        printf("1. Process Control\n");
        printf("2. File Management\n");
        printf("3. Communication\n");
        printf("4. Information Maintenance\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                process_control_example();
                break;
            case 2:
                file_management_example();
                break;
            case 3:
                communication_example();
                break;
            case 4:
                information_maintenance_example();
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}
