#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

// int main()
// {
//     int pd[2];

//     if (pipe(pd) == 0)
//     {
//         char message[] = "This is sent from pipe";
//         write(pd[1], message, strlen(message) + 1);

//         char received_message[100];
//         read(pd[0], received_message, sizeof(received_message));
//         cout << "Message received from pipe: " << received_message << endl;

//         close(fd[0]);
//         close(fd[1]);
//     }
//     else
//     {
//         perror("Pipe failed");
//     }

//     return 0;
// }

int main()
{
    const char *path = "./fifo/fifoPipe";

    mkfifo(path, 0666);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Error occurred: ");
    }
    else if (pid == 0)
    {
        // Child process
        int fd = open(path, O_RDONLY);

        if (fd < 0)
        {
            perror("File opening error: ");
        }
        char buffer[100];
        ssize_t readBytes = read(fd, buffer, sizeof(buffer));

        cout << "The child received message: " << buffer << endl;
        close(fd);
    }
    else
    {
        // Parent process
        int fd = open(path, O_WRONLY);

        if (fd < 0)
        {
            perror("File opening error: ");
        }

        char buffer[] = "This is message from parent..";
        ssize_t writeBytes = write(fd, buffer, strlen(buffer));

        if (writeBytes < 0)
        {
            perror("Error writing into file..");
        }

        close(fd);
    }
}