#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_READERS 5

// Shared resource
int data = 0;  // Example shared data

// Mutex and condition variables
pthread_mutex_t data_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t read_count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t write_cond = PTHREAD_COND_INITIALIZER;
int read_count = 0;  // Number of readers currently accessing the data

// Reader thread function
void* reader(void* arg) {
    int reader_id = *((int*)arg);

    pthread_mutex_lock(&read_count_mutex); // Lock read_count_mutex
    read_count++;  // A reader is entering
    if (read_count == 1) {
        pthread_mutex_lock(&data_mutex); // First reader locks the data
    }
    pthread_mutex_unlock(&read_count_mutex);

    // Read data
    printf("Reader %d: Read data = %d\n", reader_id, data);
    sleep(1); // Simulate reading time

    pthread_mutex_lock(&read_count_mutex); // Lock read_count_mutex
    read_count--;  // A reader is leaving
    if (read_count == 0) {
        pthread_mutex_unlock(&data_mutex); // Last reader unlocks the data
    }
    pthread_mutex_unlock(&read_count_mutex);

    return NULL;
}

// Writer thread function
void* writer(void* arg) {
    int writer_id = *((int*)arg);

    pthread_mutex_lock(&data_mutex); // Lock data for exclusive writing
    // Write data
    data++;
    printf("Writer %d: Wrote data = %d\n", writer_id, data);
    sleep(2); // Simulate writing time
    pthread_mutex_unlock(&data_mutex); // Unlock data after writing

    return NULL;
}

int main() {
    pthread_t readers[MAX_READERS], writers[2];
    int reader_ids[MAX_READERS], writer_ids[2];

    // Create 5 readers
    for (int i = 0; i < MAX_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create 2 writers
    for (int i = 0; i < 2; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    // Clean up resources
    pthread_mutex_destroy(&data_mutex);
    pthread_mutex_destroy(&read_count_mutex);
    pthread_cond_destroy(&write_cond);

    return 0;
}

