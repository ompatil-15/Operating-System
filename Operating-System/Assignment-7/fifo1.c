/*
"Before time began, there was the Cube. 
We know not where it comes from, 
only that it holds the power to create worlds and fill them with life. 
That power, the very essence of life, is called Energon. 
But, the Cube was lost to the far reaches of space, 
and we Autobots and Decepticons have spent our lives searching for it, fighting for it, 
and now, when all hope seems lost, the only hope that remains, t
he hope that any of our people can survive, lies within your hands."
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int main() {
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    int fd1 = open(FIFO1, O_WRONLY);
    int fd2 = open(FIFO2, O_RDONLY);

    if (fd1 == -1 || fd2 == -1) {
        perror("FIFO open");
        exit(1);
    }

    char sentence[1000];
    printf("Enter sentences (Type 'exit' to quit):\n");

    while (1) {
        fgets(sentence, sizeof(sentence), stdin);
        write(fd1, sentence, strlen(sentence) + 1);

        if (strcmp(sentence, "exit\n") == 0) {
            break;
        }

        char result[1000];
        read(fd2, result, sizeof(result));
        printf("Received from Process 2: %s", result);
    }

    close(fd1);
    close(fd2);

    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}

