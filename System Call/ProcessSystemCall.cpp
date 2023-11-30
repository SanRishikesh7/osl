#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("Error occurred: ");
    }
    else if (pid == 0)
    {
        cout << "Child process is running with PID: " << getpid() << endl;
        cout << "Its Parent id is: " << getppid() << endl;

        for (int i = 0; i < 5; i++)
        {
            cout << "Child is working" << endl;
            sleep(1);
        }

        cout << "Child process exiting" << endl;
        exit(1);
    }
    else
    {
        cout << "Parent process PID: " << getpid() << " and Child process PID: " << pid << endl;

        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            cout << "Child process exited normally with status: " << WEXITSTATUS(status) << endl;
        }
        else
        {
            cerr << "Child process did not exit normally." << endl;
        }

        cout << "Parent process exiting." << endl;
    }

    return 0;
}

// int main()
// {
//     pid_t p, p1, p2;

//     p = fork();

//     if (p < 0)
//     {
//         perror("Error occurred: ");
//     }
//     else if (p == 0)
//     {
//         cout << "Child process: " << getpid() << " and parent process: " << getppid() << endl;

//         p1 = fork();

//         if (p1 < 0)
//         {
//             perror("Error occurred: ");
//         }
//         else if (p1 == 0)
//         {
//             cout << "Child process: " << getpid() << " and parent process: " << getppid() << endl;
//         }
//         else
//         {
//             wait(NULL);
//             cout << "Parent with PID: " << getpid() << " is exiting" << endl;
//         }
//     }
//     else
//     {
//         wait(NULL);
//         cout << "Parent with PID: " << getpid() << " is exiting" << endl;
//     }
// }

// int main(){
//     pid_t pid;

//     if(fork() && fork()){
//         fork();
//         cout << "Hello from child" << endl;
//     }
//     cout << "Exited" << endl;

//     return 0;
// }