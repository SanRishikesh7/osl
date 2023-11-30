#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void readContent()
{
    char filename[100];
    printf("Enter filename with path: ");
    scanf("%99s", filename);

    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return;
    }

    char buffer[1000];
    ssize_t fileContent = read(fd, buffer, sizeof(buffer));

    if (fileContent < 0)
    {
        perror("Error reading content.");
        return;
    }

    printf("File content is: \n");
    printf("%s", buffer);

    close(fd);
}

void writeContent()
{
    char filename[100];
    printf("Enter filename to write content: ");
    scanf("%99s", filename);

    int fd = open(filename, O_WRONLY | O_CREAT);

    if (fd == -1)
    {
        perror("Error reading content: ");
        return;
    }

    char buffer[100];
    // char buffer1[] = "This is a sample text";
    printf("Enter content to be written: ");
    scanf("%s", buffer);
    printf("length is: %zu\n", strlen(buffer));
    ssize_t writtenBytes = write(fd, buffer, strlen(buffer));

    if (writtenBytes < 0)
    {
        perror("Error writing content: ");
        return;
    }

    printf("Content written in the file successfully.");
    close(fd);
    return;
}

void displayStats()
{
    struct stat file_info;
    if (stat("./files/sample.txt", &file_info) == 0)
    {
        printf("File size %ld", file_info.st_size);
    }
    else
    {
        perror("Error reading stats: ");
    }
    return;
}

int main()
{

    while (1)
    {
        int choice;
        printf("\n1) Read contents from file.\n");
        printf("2) Write content to file.\n");
        printf("3) Display stats.\n");
        printf("4) Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            readContent();
            break;

        case 2:
            writeContent();
            break;

        case 3:
            displayStats();
            break;

        case 4:
            printf("Thank You!!");
            exit(1);

        default:
            break;
        }
    }

    return 0;
}