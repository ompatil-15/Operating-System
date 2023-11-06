#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void callbubble(int array[], int n) {
    int d, swap, c;
    for (c = 0; c < (n - 1); c++) {
        for (d = 0; d < n - c - 1; d++) {
            if (array[d] > array[d + 1]) {
                swap = array[d];
                array[d] = array[d + 1];
                array[d + 1] = swap;
            }
        }
    }
}

int main() {
    int i, a[15], n;
    pid_t parent_id, child_id, id;
    printf("\nEnter the size of the input array: ");
    scanf("%d", &n);
    printf("\nEnter the elements of the input array: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    parent_id = getpid();
    printf("\nIn parent Process PID %d\n", parent_id);
    printf("\nSorting Numbers\n");
    callbubble(a, n);
    id = fork();
    if (id == 0) {
        child_id = getpid();
        printf("\nIn child Process PID %d\n", child_id);
        printf("\nThe Sorted Numbers are: ");
        for (i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        printf("\nExecuting execve Statement\n");
        char executable[] = "./child"; // Name of the child program
        char* arg[16];
        arg[0] = executable;
        for (i = 0; i < n; i++) {
            char str[15];
            snprintf(str, sizeof(str), "%d", a[i]);
            arg[i + 1] = (char*)malloc(strlen(str) + 1);
            strcpy(arg[i + 1], str);
        }
        arg[n + 1] = NULL;
        execve(executable, arg, NULL);
        perror("execve failed");
        printf("\nexecve Completed\n");
        printf("\nChild Complete. Now Child Exits\n");
    } else if (id > 0) {
        printf("\nIn Parent\nNow Waiting\n");
        wait(NULL);
        printf("\nParent Complete. Now Parent Exits\n");
    }
    return 0;
}

