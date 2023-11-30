#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

// Define the buffer and semaphores
int buffer[BUFFER_SIZE];
sem_t empty, full;
pthread_mutex_t mutex;

int in = 0;
int out = 0;

void *producer(void *arg)
{
    int item;
    for (int i = 0; i < 10; i++)
    {
        item = rand() % 100; // Produce a random item

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Produced by thread %ld: %d\n", (long)arg, item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int item;
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumed by thread %ld: %d\n", (long)arg, item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t producer_threads[NUM_PRODUCERS], consumer_threads[NUM_CONSUMERS];

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer threads
    for (long i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_create(&producer_threads[i], NULL, producer, (void *)i);
    }

    // Create consumer threads
    for (long i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_create(&consumer_threads[i], NULL, consumer, (void *)i);
    }

    // Wait for producer threads to finish
    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_join(producer_threads[i], NULL);
    }

    // Wait for consumer threads to finish
    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_join(consumer_threads[i], NULL);
    }

    // Clean up resources
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
