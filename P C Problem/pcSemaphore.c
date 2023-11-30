// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <semaphore.h>
// #include <unistd.h>

// #define NUM_PRODUCERS 3
// #define NUM_CONSUMERS 2
// #define N 5
// #define NUM_ITEMS 7 // Adjust the number of items to produce/consume

// sem_t mutex;
// sem_t empty;
// sem_t full;

// int buffer[N];
// int in = 0;
// int out = 0;

// int items_produced = 0;
// int items_consumed = 0;

// void *producer(void *arg)
// {
//     int id = *((int *)arg);
//     int item;
//     while (items_produced < NUM_ITEMS)
//     {
//         item = id;

//         printf("Producer %d is trying to produce item %d\n", id, item);

//         sem_wait(&empty);
//         sem_wait(&mutex);

//         buffer[in] = item;
//         in = (in + 1) % N;

//         printf("Producer %d produced item %d\n", id, item);
//         items_produced++;

//         sem_post(&mutex);
//         sem_post(&full);

//         for(int i = 0; i<N; i++){
//             printf("%d ",buffer[i]);
//         }
//         printf("\n");
//         printf("\n");

//         // usleep(rand() % 100000)
//     }
//     pthread_exit(NULL);
// }

// void *consumer(void *arg)
// {
//     int id = *((int *)arg);
//     int item;
//     while (items_consumed < NUM_ITEMS)
//     {
//         sem_wait(&full);
//         sem_wait(&mutex);

//         item = buffer[out];
//         out = (out + 1) % N;

//         printf("Consumer %d consumed item %d\n", id, item);
//         items_consumed++;

//         sem_post(&mutex);
//         sem_post(&empty);

//         // for(int i = 0; i<N; i++){
//         //     printf("%d ",buffer[i]);
//         // }
//         // printf("\n");
//         // printf("\n");
//         // usleep(rand() % 100000);
//     }
//     pthread_exit(NULL);
// }

// int main()
// {
//     srand(time(NULL));

//     sem_init(&mutex, 0, 1);
//     sem_init(&empty, 0, N);
//     sem_init(&full, 0, 0);

//     pthread_t producer_threads[NUM_PRODUCERS];
//     pthread_t consumer_threads[NUM_CONSUMERS];

//     int producer_ids[NUM_PRODUCERS];
//     int consumer_ids[NUM_CONSUMERS];

//     for (int i = 0; i < NUM_PRODUCERS; i++)
//     {
//         producer_ids[i] = i + 1;
//         pthread_create(&producer_threads[i], NULL, producer, &producer_ids[i]);
//     }

//     for (int i = 0; i < NUM_CONSUMERS; i++)
//     {
//         consumer_ids[i] = i + 1;
//         pthread_create(&consumer_threads[i], NULL, consumer, &consumer_ids[i]);
//     }

//     for (int i = 0; i < NUM_PRODUCERS; i++)
//     {
//         pthread_join(producer_threads[i], NULL);
//     }

//     for (int i = 0; i < NUM_CONSUMERS; i++)
//     {
//         pthread_join(consumer_threads[i], NULL);
//     }

//     sem_destroy(&mutex);
//     sem_destroy(&empty);
//     sem_destroy(&full);

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2
#define NUM_ITEMS 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void printBuffer() {
    printf("Buffer: ");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

void *producer(void *arg)
{
    int producer_id = *((int *)arg);
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        int item = i + 1; // Produce an item

        sem_wait(&empty); // Wait for an empty space in the buffer
        pthread_mutex_lock(&mutex); // Acquire mutex for buffer access

        // Produce item into the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Producer %d produced item %d\n", producer_id, item);
        printBuffer(); // Print buffer after producing

        if ((in + 1) % BUFFER_SIZE == out) {
            printf("Buffer is full.\n");
        }

        pthread_mutex_unlock(&mutex); // Release mutex for buffer access
        sem_post(&full); // Signal that the buffer is no longer empty

        usleep(rand() % 100000); // Sleep for a random time
    }
    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int consumer_id = *((int *)arg);
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        sem_wait(&full); // Wait for items in the buffer
        pthread_mutex_lock(&mutex); // Acquire mutex for buffer access

        // Consume item from the buffer
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumer %d consumed item %d\n", consumer_id, item);
        printBuffer(); // Print buffer after consuming

        if (in == out) {
            printf("Buffer is empty.\n");
        }

        pthread_mutex_unlock(&mutex); // Release mutex for buffer access
        sem_post(&empty); // Signal that the buffer is no longer full

        usleep(rand() % 100000); // Sleep for a random time
    }
    pthread_exit(NULL);
}

int main()
{
    srand(time(NULL));

    sem_init(&empty, 0, BUFFER_SIZE); // Initialize empty semaphore to buffer size
    sem_init(&full, 0, 0); // Initialize full semaphore to 0
    pthread_mutex_init(&mutex, NULL);

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

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
