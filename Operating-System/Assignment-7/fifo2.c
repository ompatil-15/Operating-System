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

    int fd1 = open(FIFO1, O_RDONLY);
    int fd2 = open(FIFO2, O_WRONLY);

    if (fd1 == -1 || fd2 == -1) {
        perror("FIFO open");
        exit(1);
    }

    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        perror("File open");
        exit(1);
    }

    char sentence[1000];
    char result[1000];

    while (1) {
        read(fd1, sentence, sizeof(sentence));
        printf("Received from Process 1: %s", sentence);

        if (strcmp(sentence, "exit\n") == 0) {
            break;
        }

        int charCount = 0, wordCount = 0, lineCount = 0;
        for (int i = 0; sentence[i] != '\0'; i++) {
            charCount++;
            if (sentence[i] == ' ' || sentence[i] == '\n') {
                wordCount++;
            }
            if (sentence[i] == '.') {
                lineCount++;
            }
        }

        snprintf(result, sizeof(result), "Characters: %d, Words: %d, Lines: %d\n", charCount, wordCount, lineCount);
	fprintf(outputFile, "%s", result);
        write(fd2, result, strlen(result) + 1);
    }

    close(fd1);
    close(fd2);
    fclose(outputFile);

    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}

