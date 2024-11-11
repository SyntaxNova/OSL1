#include <stdio.h>

// Function to implement LRU Page Replacement Algorithm
void LRUPageReplacement(int pages[], int n, int frameSize) {
    int frames[frameSize];
    int pageFaults = 0;
    int time[frameSize];  // Track the last used time of each page
    int counter = 0;      // Counter to simulate the clock for LRU

    // Initialize frames with -1 (indicating empty)
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
        time[i] = -1;  // Initialize time to -1, indicating no page is in memory
    }

    // Traverse the page reference string
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pageFound = 0;
        
        // Check if the page is already in the frame (page hit)
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                time[j] = counter++;  // Update the last used time of the page
                break;
            }
        }

        // If the page is not found (page fault)
        if (!pageFound) {
            pageFaults++;
            
            // If there is space in the frame, place the page
            int lru = 0;
            if (counter < frameSize) {
                lru = counter++;  // Get the next available slot
                frames[lru] = page;
                time[lru] = counter;
            } else {
                // Find the least recently used page (the one with the smallest time)
                lru = 0;
                for (int j = 1; j < frameSize; j++) {
                    if (time[j] < time[lru]) {
                        lru = j;
                    }
                }
                // Replace the least recently used page
                frames[lru] = page;
                time[lru] = counter;
                counter++;
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

    // Call the LRU Page Replacement function
    LRUPageReplacement(pages, n, frameSize);

    return 0;
}

