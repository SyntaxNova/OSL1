#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>  // For sleep function

#define BUFFER_SIZE 5
#define MAX_ITEMS 10  // Maximum number of items to produce and consume

// Shared buffer
int buffer[BUFFER_SIZE];
int in = 0, out = 0;  // Pointers to insert and remove items

// Semaphores
sem_t empty, full;     // Counting semaphores
pthread_mutex_t mutex; // Mutex for critical section

// Shared variable to track number of items produced/consumed
int items_produced = 0;
int items_consumed = 0;

// Producer thread function
void* producer(void* arg) {
    int item;
    while (items_produced < MAX_ITEMS) {  // Terminate after producing MAX_ITEMS
        item = rand() % 100; // Produce a random item
        
        sem_wait(&empty); // Wait if no empty slots
        pthread_mutex_lock(&mutex); // Enter critical section

        buffer[in] = item; // Add item to the buffer
        printf("Produced: %d at buffer[%d]\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&full);  // Signal that an item is added

        items_produced++;  // Increment the number of produced items

        sleep(1); // Sleep to simulate time taken for production
    }
    return NULL;
}

// Consumer thread function
void* consumer(void* arg) {
    int item;
    while (items_consumed < MAX_ITEMS) {  // Terminate after consuming MAX_ITEMS
        sem_wait(&full); // Wait if buffer is empty
        pthread_mutex_lock(&mutex); // Enter critical section

        item = buffer[out]; // Remove item from the buffer
        printf("Consumed: %d from buffer[%d]\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Exit critical section
        sem_post(&empty);  // Signal that an empty slot is available

        items_consumed++;  // Increment the number of consumed items

        sleep(1); // Sleep to simulate time taken for consumption
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Initially, all slots are empty
    sem_init(&full, 0, 0);            // Initially, the buffer is empty
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    printf("Producer and Consumer have finished.\n");
    return 0;
}

