#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

//fork() is a system call used to create new process. 
//the new process is called child process, and the process that initiated it (using fork()) is called parent process.
//child process is duplicate of the parent process by default.
//fork() returns 0 to the child process and returns process id of child to parent process.
//fork() returns -1 if child process is not created.
//child has same code as the parent process but the memory space is different.

pid_t p;
// Declare the function before using it
void forkSyscall();
int creatingP1P2FrP();
int heirarchyOfProcesses();
int creatingOrphan();
int orphanTest();
void zombie();
void PIPE();
void FIFO();
int main() {

    //forkSyscall();
    //creatingP1P2FrP();
    //heirarchyOfProcesses();
    //creatingOrphan();
    //orphanTest();
    //zombie();
    PIPE();
    FIFO();
    return 0;

}

void forkSyscall() {
    //we will look at the fork() sys simulation
    printf("Before fork\n");
    p = fork();

    if(p==-1){
        printf("Error in fork\n");
    }
    if(p==0){
        printf("I am child having id %d\n", getpid());
        printf("My parent's id is %d\n", getppid());
    }else {
        printf("I am child having id  %d\n", getpid());
        printf("My parent's id is %d\n", getppid());
    }

    printf("common statement\n");
}

int creatingP1P2FrP() {
    printf("\n\n");
    printf("Before fork\n");
    pid_t p1,p2;
    
    p1 = fork();

    if(p1 == -1) {
        printf("Error in fork\n");
        return 1;
    }else if(p1 == 0) {
        printf("I am child P1 having id %d\n", getpid());
        return 0;
    }else {
        //code for parent process 
        printf("this is the parent process \n (Parent P) : PID = %d\n", getpid());

        p2 = fork();

        if(p2 == -1) {
            printf("Error in fork\n");
            return 1;
        }else if(p2 == 0) {
            printf("I am child P2 having id %d\n", getpid());
            return 0;
        }else {
            //code for parent process 
            printf("this is the parent process \n (Parent P) : PID = %d\n", getpid());
        }

        wait(NULL);
        wait(NULL);

        printf("Parent process exiting\n");
    }

    return 0;
}

int heirarchyOfProcesses() {
    printf("\n\n");
    printf("Before fork\n");
    pid_t p1,p2,p;
    
    p1 = fork();

    if(p1 == -1) {
        printf("Error in fork\n");
        return 1;
    }else if(p1 == 0) {
        printf("I am child P1 having id %d\n and Parent id:: %d\n", getpid(), getppid());

        p2 = fork();

        if(p2==-1) {
            printf("Error in fork\n");
            return 1;
        }else if(p2==0){
            printf("I am child P2 having id %d\n and Parent id:: %d\n", getpid(), getppid());
            return 0;
        }
        return 0;
    }else {
        //code for parent process 
      // Code for the parent process (P)
      wait(NULL);
        printf("This is the parent process (P), PID: %d\n", getpid());

        // Parent process waits for the first child process (P1) to finish
        wait(NULL);

        printf("Parent process exiting.\n");
    }

    return 0;
}

int creatingOrphan() {
    //An orphan process is a process whose parent process has finished or terminated, though it remains running itself.
    pid_t p1;
    p1 = fork();

    if(p1 == -1) {
        printf("Error in fork\n");
        return 0;
    } else if(p1 == 0) {
        sleep(5);
        printf("I am child P having id %d\n and Parent id:: %d\n", getpid(), getppid());


    }else {
        printf("I am parent P1 running now %d\n", getpid());
        printf("and my chil is %d\n", p1);
    }
}
//Create two child process C1 and C2. Make sure that only C2 becomes an orphan process.
int orphanTest() {
    pid_t c1,c2;
    c1 = fork();

    if(c1 == -1) {
        printf("Error in fork\n");
        return 0;
    } else if(c1 == 0) {
        printf("I am child C1 having id %d\n and Parent id:: %d\n", getpid(), getppid());

        //creating c2 child
        c2 = fork();
        if(c2 == -1) {
            printf("Error in fork\n");
            return 0;
        } else if(c2 == 0) {
            sleep(5);
            printf("I am child C2 having id %d\n and Parent id:: %d\n", getpid(), getppid());
            return 0;
        } else {
            printf("I am parent C1 running now %d\n", getpid());
            printf("and my chil is %d\n", c2);
            return 0;
        }
    }else {
        printf("I am parent c1 running now %d\n", getpid());
        printf("and my chil is %d\n", c1);
    }
}


//Zombie process
void zombie() {
    //zombie is a process which has terminated but its entry still exists in the process table untill
    //the parent terminates normally or calss wait(). 

    pid_t z;
    z = fork();

    if(z==0) {
        printf("I am child z having id %d\n and Parent id::: %d\n", getpid(), getppid());

    }else {
        printf("Parent having id %d\n",getpid());
        sleep(15);
    }
}

void PIPE() {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("Error creating the pipe");
        return;
    }

    pid_t pid = fork();

    if (pid == 0) {
        close(pipefd[1]);

        char buffer[29];

        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer));

        if (bytesRead > 0) {
            printf("Child Process Received --> %s\n", buffer);
        } else {
            perror("Error reading from pipe");
        }

        close(pipefd[0]);
    } else if (pid > 0) {
        close(pipefd[0]);
        const char* message = "Hello World, This is a pipe ";
        ssize_t bytesWritten = write(pipefd[1], message, strlen(message) + 1);

        if (bytesWritten == -1) {
            perror("Error writing to pipe");
        }
        close(pipefd[1]);
    } else {
        perror("Fork failed");
    }
    return;
}

void FIFO() {
    const char* fifoPath = "input.txt";

    if (mkfifo(fifoPath, 0666) == -1) {
        perror("Error creating the FIFO");
        return;
    }

    int fd = open(fifoPath, O_WRONLY);
    if (fd == -1) {
        perror("Error opening the FIFO");
        return;
    }

    const char* message = "Hello, FIFO";
    ssize_t bytesWritten = write(fd, message, strlen(message) + 1);

    if (bytesWritten == -1) {
        perror("Error writing to FIFO");
        return;
    }

    close(fd);
    return;
}

