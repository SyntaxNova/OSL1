#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define SHM_KEY 1234  // Unique key for shared memory
#define SHM_SIZE 1024  // Size of shared memory

int main() {
    int shm_id;
    char *shm_ptr;

    // Create shared memory segment
    shm_id = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);  // Create shared memory
    if (shm_id == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach the shared memory segment to the server's address space
    shm_ptr = (char*) shmat(shm_id, NULL, 0);  // Attach the shared memory
    if (shm_ptr == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    // Write a message to the shared memory segment
    strcpy(shm_ptr, "Hello from Server!");

    printf("Server: Message written to shared memory.\n");

    // Wait for the client to read the message
    printf("Server: Press Enter to exit...\n");
    getchar();

    // Detach the shared memory segment
    shmdt(shm_ptr);

    return 0;
}

