#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void cLook(int arr[], int n, int head) {
    // Sort the request array
    sort(arr, n);
    
    int distance = 0, cur = head;
    
    // Find the index of the first request greater than or equal to the head position
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] >= head) {
            break;
        }
    }
    
    // Traverse the requests from head to the end
    for (int j = i; j < n; j++) {
        distance += abs(arr[j] - cur);
        cur = arr[j];
    }
    
    // Now, move to the first request in the sorted array
    // Traverse the requests from the lowest to the head position
    for (int j = 0; j < i; j++) {
        distance += abs(arr[j] - cur);
        cur = arr[j];
    }

    printf("Total Seek Distance: %d\n", distance);
}

int main() {
    int n, head;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the disk requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    cLook(arr, n, head);
    
    return 0;
}

