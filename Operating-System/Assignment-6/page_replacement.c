#include <stdio.h>
#include <stdbool.h>

// Function to check if a page is present in the frames
bool isPagePresent(int frames[], int frameSize, int page) {
    for (int i = 0; i < frameSize; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Function to display the frames
void displayFrames(int frames[], int frameSize) {
    for (int i = 0; i < frameSize; i++) {
        if (frames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d ", frames[i]);
        }
    }
    printf("\n");
}

// First-Come-First-Served (FCFS) Page Replacement Algorithm
void FCFS(int referenceString[], int referenceSize, int frameSize) {
    int frames[frameSize];
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
    }
    int pageFaults = 0;
    int frameIndex = 0;

    printf("\nFCFS Page Replacement Algorithm:\n");
    for (int i = 0; i < referenceSize; i++) {
        int page = referenceString[i];
        if (!isPagePresent(frames, frameSize, page)) {
            frames[frameIndex] = page;
            frameIndex = (frameIndex + 1) % frameSize;
            pageFaults++;
        }
        displayFrames(frames, frameSize);
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

// Least Recently Used (LRU) Page Replacement Algorithm
void LRU(int referenceString[], int referenceSize, int frameSize) {
    int frames[frameSize];
    int counter[frameSize];
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }
    int pageFaults = 0;

    printf("\nLRU Page Replacement Algorithm:\n");
    for (int i = 0; i < referenceSize; i++) {
        int page = referenceString[i];
        if (!isPagePresent(frames, frameSize, page)) {
            int minCounter = counter[0];
            int replaceIndex = 0;
            for (int j = 0; j < frameSize; j++) {
                if (counter[j] < minCounter) {
                    minCounter = counter[j];
                    replaceIndex = j;
                }
            }
            frames[replaceIndex] = page;
            counter[replaceIndex] = 0;
            pageFaults++;
        }
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] != -1) {
                counter[j]++;
            }
        }
        displayFrames(frames, frameSize);
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

// Optimal Page Replacement Algorithm
void Optimal(int referenceString[], int referenceSize, int frameSize) {
    int frames[frameSize];
    int pageFaults = 0;

    printf("\nOptimal Page Replacement Algorithm\n\n");
    for (int i = 0; i < frameSize; i++) {
        frames[i] = -1;
    }
    for (int i = 0; i < referenceSize; i++) {
        int page = referenceString[i];
        if (!isPagePresent(frames, frameSize, page)) {
            int replaceIndex = -1;
            for (int j = 0; j < frameSize; j++) {
                if (!isPagePresent(referenceString + i + 1, referenceSize - i - 1, frames[j])) {
                    replaceIndex = j;
                    break;
                }
            }
            if (replaceIndex == -1) {
                int farthest = 0;
                for (int j = 0; j < frameSize; j++) {
                    int nextPageIndex = i + 1;
                    while (nextPageIndex < referenceSize) {
                        if (frames[j] == referenceString[nextPageIndex]) {
                            if (nextPageIndex > farthest) {
                                farthest = nextPageIndex;
                                replaceIndex = j;
                            }
                            break;
                        }
                        nextPageIndex++;
                    }
                }
            }
            frames[replaceIndex] = page;
            pageFaults++;
        }
        displayFrames(frames, frameSize);
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int referenceString[] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5};
    int referenceSize = sizeof(referenceString) / sizeof(referenceString[0]);
    int frameSize = 3;

    int choice;
    do {
        printf("\nPage Replacement Algorithms Menu\n\n");
        printf("1 - FCFS\n");
        printf("2 - LRU\n");
        printf("3 - Optimal\n");
        printf("4 - Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                FCFS(referenceString, referenceSize, frameSize);
                break;
            case 2:
                LRU(referenceString, referenceSize, frameSize);
                break;
            case 3:
                Optimal(referenceString, referenceSize, frameSize);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}

