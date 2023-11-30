#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
// #include <unistd.h> 

sem_t resource_mutex; 
sem_t readers_count_mutex;
int shared_resource = 0;
int readers = 0;

void *reader(void *arg) {
    int id = *((int *)arg);
    printf("Reader %d is trying to Read\n",id);

    sem_wait(&readers_count_mutex);
    readers++;
    if (readers == 1) {
        sem_wait(&resource_mutex); 
    }
    sem_post(&readers_count_mutex);

    
    printf("Reader %d read: %d\n", id, shared_resource);

    sem_wait(&readers_count_mutex);
    readers--;
    if (readers == 0) {
        sem_post(&resource_mutex); 
    }
    sem_post(&readers_count_mutex);
    printf("Reader %d is exitting \n",id);

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *((int *)arg);
    printf("Writer %d is trying to write\n",id);

    sem_wait(&resource_mutex); 


    shared_resource = id;
    printf("Writer %d wrote: %d\n", id, shared_resource);

    sem_post(&resource_mutex); 
    printf("Writer %d is exitting \n",id);

    pthread_exit(NULL);
}

int main() {
    int num_readers = 3;
    int num_writers = 5;

    sem_init(&resource_mutex, 0, 1); 
    sem_init(&readers_count_mutex, 0, 1); 

    pthread_t reader_threads[num_readers];
    pthread_t writer_threads[num_writers];

    int reader_ids[num_readers];
    int writer_ids[num_writers];

    for (int i = 0; i < num_readers; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < num_writers; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < num_readers; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    for (int i = 0; i < num_writers; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    sem_destroy(&resource_mutex);
    sem_destroy(&readers_count_mutex);

    return 0;
}
