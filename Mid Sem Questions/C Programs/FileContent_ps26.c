#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int main()
{
    char filename[100];
    struct stat fileStat;

    printf("Enter the filename: ");
    scanf("%s", filename);

    // Check if the file exists
    if (stat(filename, &fileStat) < 0)
    {
        perror("File not found");
        return 1;
    }

    printf("File Properties for %s:\n", filename);
    printf("1. File Size: %ld bytes\n", fileStat.st_size);
    printf("2. Inode Number: %ld\n", fileStat.st_ino);
    printf("3. Device ID: %ld\n", fileStat.st_dev);
    printf("4. Number of Hard Links: %ld\n", fileStat.st_nlink);
    printf("5. User ID of Owner: %d\n", fileStat.st_uid);
    printf("6. Group ID of Owner: %d\n", fileStat.st_gid);
    printf("7. File Type and Mode: %o\n", fileStat.st_mode);
    printf("8. Last Access Time: %s", ctime(&fileStat.st_atime));
    printf("9. Last Modification Time: %s", ctime(&fileStat.st_mtime));
    printf("10. Last Status Change Time: %s", ctime(&fileStat.st_ctime));

    return 0;
}
