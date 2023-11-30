#include<unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Open a file for writing
    int fileDescriptor = open("example.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    if (fileDescriptor == -1) {
        // Handle error if the file couldn't be opened
       
        return 1;
    }
    ssize_t bytesWritten = write(fileDescriptor, "Hello World\n", 12); //1, is the file descriptor, Hello World\n is data, and 12 is the length of the data
    lseek(fileDescriptor, 12, SEEK_SET);
    bytesWritten = write(fileDescriptor, "How are you\n", 12); //1, is the file descriptor, Hello World\n is data, and 12 is the length of the data
    if (bytesWritten == -1) {
        // Handle error if the write operation fails
       
        close(fileDescriptor);  // Close the file descriptor
        return 1;
    }

     


    //Read
    char buff[30];
    int fd = open("example.txt", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);

    ssize_t bytesRead = read(fd, buff, 24); //1, is the file descriptor, Hello World\n is data, and 12 is the length of the data

    if (bytesRead == -1) {
        // Handle error if the write operation fails
       
        close(fd);  // Close the file descriptor
        return 1;
    }

    write(STDOUT_FILENO, buff, bytesRead);
     // Close the file descriptor

    

//     The write() system call takes three parameters: “1” which is the file descriptor of the file where we want to write. 
//Since we want to write on standard output device which is the screen, hence the file descriptor, in this case, is ‘1’, 
//which is fixed (0 is the file descriptor for standard input device (e.g. keyboard) and 2 is for standard error device)).
// Next thing is what we want to write on the screen. In this case its “hello\n” i.e. hello and newline(\n), so a total of 6 characters,
// which becomes the third parameter. The third parameter is how much you want to write, 
//which may be less than the data specified in the second parameter. You can play around and see the change in output.
//     //gcc writesys.c -o writesys

//creating the dubplicate
int fd2 = dup(fileDescriptor);
write(fd2, "Siddhesh\n", 9);
close(fd2);

return 0;
}