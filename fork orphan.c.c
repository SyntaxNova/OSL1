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

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process: performs selection sort
        sleep(2);  // Delay to allow parent to exit first
        selectionSort(arr, n);
        printf("Child (orphan) process sorted: ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
        printf("Child (orphan) process completed with PID %d and PPID %d\n", getpid(), getppid());
    } else {
        // Parent process: performs bubble sort
        bubbleSort(arr, n);
        printf("Parent process sorted: ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
        printf("Parent process exiting, leaving child process orphaned...\n");
        exit(0);  // Parent exits immediately
    }

    return 0;
}

