#include <stdio.h>
#include <stdlib.h>

// Function to calculate the absolute difference between two numbers
int abs_diff(int a, int b) {
    return (a > b) ? a - b : b - a;
}

// Function to find the index of the request with the minimum seek time
int find_min_seek_time(int requests[], int n, int head, int visited[]) {
    int min_diff = abs_diff(head, requests[0]);
    int min_index = 0;

    for (int i = 1; i < n; i++) {
        if (!visited[i]) {
            int diff = abs_diff(head, requests[i]);
            if (diff < min_diff) {
                min_diff = diff;
                min_index = i;
            }
        }
    }
    return min_index;
}

// Function to implement SSTF Disk Scheduling Algorithm
void sstf(int requests[], int n, int head) {
    int total_seek_time = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;  // Initialize all requests as unvisited

    printf("Disk Scheduling Order: ");
    
    // Process all the requests
    for (int i = 0; i < n; i++) {
        // Find the unvisited request with the minimum seek time
        int index = find_min_seek_time(requests, n, head, visited);
        
        // Add the seek time to the total seek time
        total_seek_time += abs_diff(head, requests[index]);
        
        // Update the head to the new position
        head = requests[index];
        
        // Mark the request as visited
        visited[index] = 1;
        
        // Print the request served
        printf("%d ", requests[index]);
    }

    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main() {
    int n;

    // Taking input for the number of disk requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];
    
    // Taking input for the disk requests
    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    int head;
    // Taking input for the initial head position
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    sstf(requests, n, head);

    return 0;
}

