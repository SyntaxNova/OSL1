#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

#define SHM_KEY 1234  // Same key as used by server
#define SHM_SIZE 1024  // Size of shared memory

int main() {
    int shm_id;
    char *shm_ptr;

    // Get the shared memory segment created by the server
    shm_id = shmget(SHM_KEY, SHM_SIZE, 0666);  // Access the shared memory
    if (shm_id == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach the shared memory segment to the client's address space
    shm_ptr = (char*) shmat(shm_id, NULL, 0);  // Attach the shared memory
    if (shm_ptr == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Read the message from shared memory and print it
    printf("Client: Received message: %s\n", shm_ptr);

    // Detach the shared memory segment
    shmdt(shm_ptr);

    return 0;
}

