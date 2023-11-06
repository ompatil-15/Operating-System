#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    key_t key = ftok("/tmp", 'S'); // Generate a key for the shared memory segment.

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a shared memory segment.
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    
    printf("\n[ Server ] Enter a message to store in shared memory (or 'exit' to quit)");	
    // Continuously write messages to shared memory.
    while (1) {
        // Attach to the shared memory segment.
        char *shm = shmat(shmid, NULL, 0);
        if (shm == (char *)-1) {
            perror("shmat");
            exit(1);
        }

        // Ask the user to enter a message.
        printf("[ Server ] Message: ");
        fgets(shm, SHM_SIZE, stdin);

        if (strcmp(shm, "exit\n") == 0) {
            break;
        }

        // Detach from the shared memory segment.
        shmdt(shm);
    }

    // Remove the shared memory segment when done.
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

