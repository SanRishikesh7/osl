#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE];
int itemCount = 0;
pthread_mutex_t mutex;
pthread_t producers[NUM_PRODUCERS];
pthread_t consumers[NUM_CONSUMERS];

void* producer(void* id) {
    int producer_id = *((int*)id);
    free(id);

    for (int i = 1; i <= 10; i++) {
        int product = rand() % 100;
        
        pthread_mutex_lock(&mutex);
        while (itemCount == BUFFER_SIZE) {
            printf("Producer %d is waiting. Buffer is full.\n", producer_id);
            pthread_mutex_unlock(&mutex);
            usleep(rand() % 1000000);  // Sleep for a random amount of time
            pthread_mutex_lock(&mutex);
        }

        buffer[itemCount++] = product;
        printf("Producer %d produced product %d. Buffer size: %d\n", producer_id, product, itemCount);
        pthread_mutex_unlock(&mutex);
        usleep(rand() % 1000000);  // Sleep for a random amount of time
    }

    return NULL;
}

void* consumer(void* id) {
    int consumer_id = *((int*)id);
    free(id);

    for (int i = 1; i <= 10; i++) {
        pthread_mutex_lock(&mutex);
        while (itemCount == 0) {
            printf("Consumer %d is waiting. Buffer is empty.\n", consumer_id);
            pthread_mutex_unlock(&mutex);
            usleep(rand() % 1000000);  // Sleep for a random amount of time
            pthread_mutex_lock(&mutex);
        }

        int product = buffer[--itemCount];
        printf("Consumer %d consumed product %d. Buffer size: %d\n", consumer_id, product, itemCount);
        pthread_mutex_unlock(&mutex);
        usleep(rand() % 1000000);  // Sleep for a random amount of time
    }

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        int* id = (int*)malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&producers[i], NULL, producer, id);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        int* id = (int*)malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&consumers[i], NULL, consumer, id);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    
    return 0;
}
