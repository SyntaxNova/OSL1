#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b); // Compare integers
}

void scan(int arr[], int size, int head, int disk_size) {
    int left[size], right[size];
    int left_count = 0, right_count = 0;
    int seek_count = 0, distance, curr;

    // Dividing the requests into left and right of the initial head position
    for (int i = 0; i < size; i++) {
        if (arr[i] < head) {
            left[left_count++] = arr[i];
        } else {
            right[right_count++] = arr[i];
        }
    }

    // Sorting both left and right arrays
    qsort(left, left_count, sizeof(int), compare);
    qsort(right, right_count, sizeof(int), compare);

    // Calculate the distance for right direction (moving away from spindle)
    curr = head;
    for (int i = 0; i < right_count; i++) {
        distance = abs(curr - right[i]);
        seek_count += distance;
        curr = right[i];
    }

    // After reaching the end, reverse direction and move to left
    seek_count += abs(curr - (disk_size - 1));
    curr = disk_size - 1;

    // Now process the left side
    for (int i = left_count - 1; i >= 0; i--) {
        distance = abs(curr - left[i]);
        seek_count += distance;
        curr = left[i];
    }

    printf("Total seek count: %d\n", seek_count);
    printf("Seek Sequence: ");
    for (int i = 0; i < right_count; i++) {
        printf("%d ", right[i]);
    }
    printf("%d ", disk_size - 1);
    for (int i = left_count - 1; i >= 0; i--) {
        printf("%d ", left[i]);
    }
    printf("\n");
}

int main() {
    int size, head, disk_size;

    // Taking input from the user
    printf("Enter the number of disk requests: ");
    scanf("%d", &size);

    int arr[size];

    printf("Enter the disk requests:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("Enter the total number of disk tracks: ");
    scanf("%d", &disk_size);

    // Calling the SCAN function
    scan(arr, size, head, disk_size);
    
    return 0;
}

