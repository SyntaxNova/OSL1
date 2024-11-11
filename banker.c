#include <stdio.h>
#include <stdbool.h>

#define P 5  // Number of processes
#define R 3  // Number of resource types

// Function to check if the system is in a safe state
bool isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    int work[R];
    bool finish[P] = {false}; // Finish array to mark completed processes
    int safeSeq[P]; // Array to store safe sequence

    // Calculate Need matrix
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }

    // Initialize work[] to available[] resources
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    int count = 0; // Count of processes that can finish
    while (count < P) {
        bool found = false;

        // Search for a process that can finish
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                // Check if the process can finish
                bool canFinish = true;
                for (int r = 0; r < R; r++) {
                    if (need[p][r] > work[r]) {
                        canFinish = false;
                        break;
                    }
                }

                // If the process can finish, simulate its completion
                if (canFinish) {
                    for (int r = 0; r < R; r++) {
                        work[r] += allot[p][r]; // Release resources
                    }
                    safeSeq[count++] = processes[p];
                    finish[p] = true;
                    found = true;
                    break;
                }
            }
        }

        // If no process could finish, the system is not in a safe state
        if (!found) {
            return false;
        }
    }

    // Print the safe sequence
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return true;
}

int main() {
    // Process identifiers
    int processes[] = {0, 1, 2, 3, 4};

    // Available resources
    int avail[] = {3, 3, 2};  // Available resources of type A, B, C

    // Maximum resources required by each process
    int max[][R] = {
        {5, 3, 3},
        {0, 2, 2},
        {7, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Resources allocated to each process
    int allot[][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Check if the system is in a safe state
    if (!isSafe(processes, avail, max, allot)) {
        printf("System is not in a safe state.\n");
    }

    return 0;
}

