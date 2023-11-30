#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

pthread_mutex_t buffer_mutex;

void *producer(void *arg)
{
    int producer_id = *((int *)arg);
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        int item = rand() % 100; // Produce an item

        pthread_mutex_lock(&buffer_mutex); // Acquire buffer mutex

        // Check if the buffer is full
        while ((in + 1) % BUFFER_SIZE == out)
        {
            pthread_mutex_unlock(&buffer_mutex);
            usleep(10000); // Sleep briefly to avoid busy-waiting
            pthread_mutex_lock(&buffer_mutex);
        }

        // Produce item into the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Producer %d produced item %d\n", producer_id, item);

        pthread_mutex_unlock(&buffer_mutex); // Release buffer mutex
        usleep(rand() % 100000);             // Sleep for a random time
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int consumer_id = *((int *)arg);
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        pthread_mutex_lock(&buffer_mutex); // Acquire buffer mutex

        // Check if the buffer is empty
        while (in == out)
        {
            pthread_mutex_unlock(&buffer_mutex);
            usleep(10000); // Sleep briefly to avoid busy-waiting
            pthread_mutex_lock(&buffer_mutex);
        }

        // Consume item from the buffer
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer %d consumed item %d\n", consumer_id, item);

        pthread_mutex_unlock(&buffer_mutex); // Release buffer mutex
        usleep(rand() % 100000);             // Sleep for a random time
    }
    pthread_exit(NULL);
}

int main()
{
    srand(time(NULL));

    pthread_mutex_init(&buffer_mutex, NULL);

    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];

    int producer_ids[NUM_PRODUCERS];
    int consumer_ids[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        producer_ids[i] = i + 1;
        pthread_create(&producer_threads[i], NULL, producer, &producer_ids[i]);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        consumer_ids[i] = i + 1;
        pthread_create(&consumer_threads[i], NULL, consumer, &consumer_ids[i]);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_join(producer_threads[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_join(consumer_threads[i], NULL);
    }

    pthread_mutex_destroy(&buffer_mutex);

    return 0;
}
