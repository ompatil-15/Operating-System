#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int a[10], i, m, c = 0, l, u, mid;
    printf("\n\nEnter the number to be searched: ");
    scanf("%d", &m);
    for (i = 1; i < argc; i++) { // Start from i = 1
        a[i - 1] = atoi(argv[i]);
    }
    l = 0;
    u = i - 2; // Adjust u to consider the last element added
    while (l <= u) {
        mid = (l + u) / 2;
        if (m == a[mid]) {
            c = 1;
            break;
        } else if (m < a[mid]) {
            u = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if (c == 0)
        printf("The number is not found\n");
    else
        printf("The number is found\n");

    return 0;
}

