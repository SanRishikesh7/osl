#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    // Open a file for writing
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write data to the file
    const char *message = "Hello I'am Using File Management System calls \nTo write and read from file!\n";
    ssize_t bytes_written = write(fd, message, strlen(message));
    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    // Close the file
    close(fd);

    // Open the file for reading
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Read data from the file and print it
    char buffer[100];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return 1;
    }
    buffer[bytes_read] = '\0';  // Null-terminate the string
    printf("Read from file: %s", buffer);

    // Close the file
    close(fd);

    return 0;
}
