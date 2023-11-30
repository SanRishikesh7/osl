#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define N 100
#define NUM_ITEMS 20 // Adjust the number of items to produce/consume

sem_t mutex;
sem_t empty;
sem_t full;

int buffer[N]; // Buffer to hold items
int in = 0;    // Index to insert into the buffer
int out = 0;   // Index to remove from the buffer

int items_produced = 0; // Counter for produced items
int items_consumed = 0; // Counter for consumed items

void *producer(void *arg)
{
    int item;
    while (items_produced < NUM_ITEMS)
    {
        item = rand() % 100; // Simulate producing an item

        printf("Producer is trying to produce item %d\n", item);

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item; // Insert item into the buffer
        in = (in + 1) % N; // Update buffer index

        printf("Producer produced item %d\n", item);
        items_produced++;

        sem_post(&mutex);
        sem_post(&full);

        usleep(rand() % 100000);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int item;
    while (items_consumed < NUM_ITEMS)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[out];  // Consume an item from the buffer
        out = (out + 1) % N; // Update buffer index

        printf("Consumer consumed item %d\n", item);
        items_consumed++;

        sem_post(&mutex);
        sem_post(&empty);

        usleep(rand() % 100000);
    }
    pthread_exit(NULL);
}

int main()
{
    srand(time(NULL));

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);

    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_create(&producer_threads[i], NULL, producer, NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_join(producer_threads[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_join(consumer_threads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
