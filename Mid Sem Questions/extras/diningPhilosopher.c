#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define MAX_MEALS 5

pthread_t philosophers[NUM_PHILOSOPHERS];
sem_t forks[NUM_PHILOSOPHERS];
sem_t mutex;

int meals_eaten[NUM_PHILOSOPHERS] = {0};

void *philosopher(void *arg)
{
    int philosopher_id = *((int *)arg);
    int left_fork = philosopher_id;
    int right_fork = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    while (meals_eaten[philosopher_id] < MAX_MEALS)
    {
        printf("Philosopher %d is thinking\n", philosopher_id);

        sem_wait(&mutex);
        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);
        sem_post(&mutex);

        printf("Philosopher %d is eating\n", philosopher_id);
        meals_eaten[philosopher_id]++;

        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);

        printf("Philosopher %d finished eating %d meals\n", philosopher_id, meals_eaten[philosopher_id]);

        usleep(1000000); // Sleep for a while to allow others to run
    }

    pthread_exit(NULL);
}

int main()
{
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        int *philosopher_id = malloc(sizeof(int));
        *philosopher_id = i;
        pthread_create(&philosophers[i], NULL, philosopher, philosopher_id);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        sem_destroy(&forks[i]);
    }

    sem_destroy(&mutex);

    return 0;
}
