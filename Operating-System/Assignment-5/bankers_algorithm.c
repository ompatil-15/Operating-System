#include <stdio.h>

int main() {
    int processes, resources;
    printf("\nEnter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    int max[processes][resources];
    int allocation[processes][resources];
    int need[processes][resources];
    int available[resources];

    // For quick testing, you can uncomment and use these predefined values.
    // Be sure to update them as needed or use your own test values.

    /*
    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int allocation[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int available[3] = {3, 3, 2};
    */

    // Input maximum resources each process can request
    printf("\nEnter the maximum resource matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input resources currently allocated to processes
    printf("\nEnter the resource allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Calculate the resource need matrix
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Input the available resources
    printf("\nEnter the available resources vector:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    int finish[processes];
    for (int i = 0; i < processes; i++) {
        finish[i] = 0;
    }

    int safeSequence[processes];
    int work[resources];

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int count = 0;

    while (count < processes) {
        int found = 0;

        for (int i = 0; i < processes; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < resources; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == resources) {
                    for (j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            printf("\nThe system is in an unsafe state. Deadlock detected.\n");
            return 0;
        }
    }

    printf("\nSafe sequence: ");
    for (int i = 0; i < processes; i++) {
        printf("P%d", safeSequence[i]);
        if (i < processes - 1) {
            printf(" -> ");
        }
    }
    printf("\n");

    return 0;
}

