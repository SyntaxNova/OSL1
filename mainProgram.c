#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sort_array(int arr[], int n) {
    // Bubble sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        sort_array(arr, n);  // Sort the array in ascending order

        // Prepare arguments for execve
        char *args[n + 2];  // n elements + program name + NULL
        args[0] = "./reverse";  // Program name

        for (int i = 0; i < n; i++) {
            char *num_str = malloc(10 * sizeof(char));
            sprintf(num_str, "%d", arr[i]);
            args[i + 1] = num_str;
        }

        args[n + 1] = NULL;  // Last argument should be NULL

        // Execute display_reverse program
        execve(args[0], args, NULL);

        // If execve returns, it must have failed
        perror("execve failed");
        exit(1);
    } else {
        // Parent process
        wait(NULL);  // Wait for the child to complete
        printf("Child process completed.\n");
    }

    return 0;
}

