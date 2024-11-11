#include <stdio.h>
#include <limits.h>

// Function to implement Optimal Page Replacement Algorithm
void OptimalPageReplacement(int pages[], int n, int frameSize) {
    int frames[frameSize];
    int pageFaults = 0;

    // Initialize frames with -1 (indicating empty frames)
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
    }

    // Traverse through the page reference string
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pageFound = 0;

        // Check if the page is already in the frames (Page Hit)
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        // If page is not found in the frames (Page Fault)
        if (!pageFound) {
            pageFaults++;
            
            // If there's space in the frames, insert the new page
            int frameEmpty = -1;
            for (int j = 0; j < frameSize; j++) {
                if (frames[j] == -1) {
                    frameEmpty = j;
                    break;
                }
            }

            if (frameEmpty != -1) {
                // If there's an empty slot, insert the page directly
                frames[frameEmpty] = page;
            } else {
                // If no empty slot, find the page to replace (page with farthest next reference)
                int farthest = -1, replaceIndex = -1;

                for (int j = 0; j < frameSize; j++) {
                    int nextUse = -1;
                    // Find the next occurrence of frames[j] in the future reference string
                    for (int k = i + 1; k < n; k++) {
                        if (pages[k] == frames[j]) {
                            nextUse = k;
                            break;
                        }
                    }

                    // If the page does not occur in the future, select it for replacement
                    if (nextUse == -1) {
                        replaceIndex = j;
                        break;
                    }

                    // Select the page that has the farthest future use
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }

                // Replace the page with the farthest next use
                frames[replaceIndex] = page;
            }

            // Print the current state of the frames after a page fault
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

    // Call the Optimal Page Replacement function
    OptimalPageReplacement(pages, n, frameSize);

    return 0;
}

