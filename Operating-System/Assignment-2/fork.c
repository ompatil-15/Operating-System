#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function to sort an array of integers using the Bubble Sort algorithm
void bubbleSort(int arr[], int n) {
    int temp, swapped;
    do {
        swapped = 0;
        for (int i = 1; i < n; i++) {
            if (arr[i - 1] > arr[i]) {
                // Swap arr[i-1] and arr[i]
                temp = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = temp;
                swapped = 1;
            }
        }
    } while (swapped);
}

int main() {
    int n, status;
    printf("\nEnter the number of integers to sort: ");
    scanf("%d", &n);

    int* numbers = (int*)malloc(n * sizeof(int));

    // Input the integers
    printf("Enter the integers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        // Forking failed
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID %d) is sorting the integers...\n", getpid());
        bubbleSort(numbers, n);
        printf("Child process (PID %d) sorted the integers.\n", getpid());
    } else {
        // Parent process
        printf("Parent process (PID %d) is waiting for the child process (PID %d) to complete...\n", getpid(), pid);
        wait(&status);
        printf("Parent process (PID %d) finished waiting for the child process.\n", getpid());

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d.\n", WEXITSTATUS(status));
        }

        printf("Sorted integers: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", numbers[i]);
        }
        printf("\n");
    }

    free(numbers);

    return 0;
}

