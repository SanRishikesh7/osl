#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> // For usleep function

pthread_mutex_t resource_mutex;
pthread_mutex_t readers_count_mutex;
int shared_resource = 0;
int readers = 0;

void *reader(void *arg) {
    int id = *((int *)arg);
    printf("Reader %d is trying to Read\n",id);

    pthread_mutex_lock(&readers_count_mutex);
    readers++;
    if (readers == 1) {
        pthread_mutex_lock(&resource_mutex); // Lock the resource for the first reader
    }

    pthread_mutex_unlock(&readers_count_mutex);

    // Reading the shared resource
    printf("Reader %d read: %d\n", id, shared_resource);
    usleep(1000000); 

    pthread_mutex_lock(&readers_count_mutex);
    readers--;
    if (readers == 0) {
        pthread_mutex_unlock(&resource_mutex); // Unlock the resource when the last reader is done
    }
    pthread_mutex_unlock(&readers_count_mutex);
    printf("Reader %d is exitting \n",id);

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *((int *)arg);
    printf("Writer %d is trying to write\n",id);

    pthread_mutex_lock(&resource_mutex);

    // Writing to the shared resource
    sd;
    printf("Wrhared_resource = iiter %d wrote: %d\n", id, shared_resource);

    pthread_mutex_unlock(&resource_mutex);

    printf("Writer %d is exitting \n",id);

    pthread_exit(NULL);
}

int main() {
    int num_readers = 4;
    int num_writers = 3;

    pthread_mutex_init(&resource_mutex, NULL);
    pthread_mutex_init(&readers_count_mutex, NULL);

    pthread_t reader_threads[num_readers];
    pthread_t writer_threads[num_writers];

    int reader_ids[num_readers];
    int writer_ids[num_writers];


    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }
    
    for (int i = 0; i < num_readers; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }


    for (int i = 0; i < num_readers; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    for (int i = 0; i < num_writers; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    pthread_mutex_destroy(&resource_mutex);
    pthread_mutex_destroy(&readers_count_mutex);

    return 0;
}