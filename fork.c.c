#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        int temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    pid_t pid = fork();

    if (pid == 0) {  // Child process
        selectionSort(arr, n);
        printf("Child sorted: ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
        exit(0);
    } else {  // Parent process
        bubbleSort(arr, n);
        printf("Parent sorted: ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
        wait(NULL);  // Wait for child to finish
        sleep(10);   // Demonstrate zombie state briefly
        printf("Parent process done.\n");
    }
    return 0;
}

