#include <stdio.h>

// Function to implement FCFS Page Replacement Algorithm
void FCFSPageReplacement(int pages[], int n, int frameSize) {
    int frames[frameSize];
    int pageFaults = 0;
    int index = 0;
    
    // Initialize frames with -1 (indicating empty)
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
    }

    // Traverse the page reference string
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pageFound = 0;

        // Check if the page is already in the frame (page hit)
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        // If the page is not found (page fault)
        if (!pageFound) {
            pageFaults++;

            // If there is space in the frame, place the page
            if (index < frameSize) {
                frames[index++] = page;
            } else {
                // Replace the first page that came in (FCFS)
                for (int j = 0; j < frameSize - 1; j++) {
                    frames[j] = frames[j + 1];
                }
                frames[frameSize - 1] = page;
            }

            // Print the current state of the frames
            printf("Page Fault! Frames: ");
            for (int j = 0; j < frameSize; j++) {
                if (frames[j] == -1) {
                    printf("- ");
                } else {
                    printf("%d ", frames[j]);
                }
            }
            printf("\n");
        }
    }

    // Print the total number of page faults
    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int frameSize;
    printf("Enter the frame size (at least 3): ");
    scanf("%d", &frameSize);
    if (frameSize < 3) {
        printf("Frame size must be at least 3.\n");
        return 1;  // Exit if frame size is less than 3
    }

    int n;
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Print the page reference string
    printf("Page reference string: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    // Call the FCFS Page Replacement function
    FCFSPageReplacement(pages, n, frameSize);

    return 0;
}

