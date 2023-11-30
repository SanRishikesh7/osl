#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void alarm_handler(int signum) {
    printf("Alarm triggered!\n");
}

int main() {
    // getpid()
    pid_t current_pid = getpid();
    printf("Current process PID: %d\n", current_pid);

    // alarm()
    signal(SIGALRM, alarm_handler);
    unsigned int seconds = 5;
    alarm(seconds);

    printf("Waiting for %d seconds...\n", seconds);
    sleep(seconds);

    // sleep()
    printf("Sleeping for 3 seconds...\n");
    sleep(3);
    printf("Awake now!\n");

    return 0;
}
