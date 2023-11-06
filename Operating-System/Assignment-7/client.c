#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    key_t key = ftok("/tmp", 'S'); // Use the same key as in the server program.

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Get the shared memory segment.
    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    char *previousData = NULL;
    char *currentData;
    
    printf("\n");
    while (1) {
        // Attach to the shared memory segment.
        currentData = shmat(shmid, NULL, 0);
        if (currentData == (char *)-1) {
            perror("shmat");
            exit(1);
        }

        // Compare the current content with the previous content.
        if (previousData == NULL || strcmp(currentData, previousData) != 0) {
            printf("[ Client ] New message read from shared memory: %s", currentData);
            if (previousData != NULL) {
                free(previousData);
            }
            previousData = strdup(currentData);
        }

        // Detach from the shared memory segment.
        shmdt(currentData);
    }

    return 0;
}

