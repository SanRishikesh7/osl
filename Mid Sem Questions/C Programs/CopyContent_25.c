#include <stdio.h>

int main()
{
    FILE *sourceFile, *destinationFile;
    char ch;

    // Open the source file in read mode
    sourceFile = fopen("source.txt", "r");
    if (sourceFile == NULL)
    {
        printf("Failed to open source file.\n");
        return 1;
    }

    // Open the destination file in write mode
    destinationFile = fopen("destination.txt", "w");
    if (destinationFile == NULL)
    {
        printf("Failed to open destination file.\n");
        fclose(sourceFile);
        return 1;
    }

    // Copy character by character
    while ((ch = fgetc(sourceFile)) != EOF)
    {
        fputc(ch, destinationFile);
    }

    // Close both files
    fclose(sourceFile);
    fclose(destinationFile);

    printf("File copied successfully character by character.\n");

    return 0;
}
