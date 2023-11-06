#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>

//look: 98 183 40 122 10 124 65; 303 333 head 53
//scan: 98 183 37 122 14 124 65 67; 236 382 head 53
	

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void sstf(int requests[], int n, int initial_head) {
    int seek_sequence[n];
    int seek_count = 0;
    int current_head = initial_head;

    // Create an array to keep track of visited requests
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    printf("SSTF Seek Sequence: %d", current_head);

    for (int i = 0; i < n; i++) {
        int min_seek = INT_MAX;
        int min_index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int seek = abs(requests[j] - current_head);
                if (seek < min_seek) {
                    min_seek = seek;
                    min_index = j;
                }
            }
        }

        seek_sequence[i] = requests[min_index];
        seek_count += min_seek;
        current_head = requests[min_index];
        visited[min_index] = 1;

        printf(" -> %d", seek_sequence[i]);
    }

    printf("\nTotal Seek Distance: %d\n", seek_count);
}

void scan(int requests[], int n, int initial_head, int direction, int track_size) {
    // Sorting the requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Stores the order in which requests are processed
    int order[n];
    int order_index = 0;

    // Stores the total head movement
    int total = 0;

    int last = initial_head;

    if (direction == 1) {
        // Extract requests with a value greater than or equal to the head and calculate the requests
        for (int i = 0; i < n; i++) {
            if (requests[i] >= initial_head) {
                total += (requests[i] - last);
                last = requests[i];
                order[order_index++] = requests[i];
            }
        }

        // Reaching the end of the disk
        total += (track_size - last - 1);
        order[order_index++] = track_size - 1;

        // Extract requests with a value less than the head and calculate the requests
        last = track_size - 1;
        for (int i = 0; i < n; i++) {
            if (requests[i] < initial_head) {
                total += (last - requests[i]);
                last = requests[i];
                order[order_index++] = requests[i];
            }
        }
    } else {
        // Reverse direction (left)
        // Extract requests with a value less than or equal to the head and calculate the requests
        for (int i = 0; i < n; i++) {
            if (requests[i] <= initial_head) {
                total += (last - requests[i]);
                last = requests[i];
                order[order_index++] = requests[i];
            }
        }

        // Reaching the starting of the disk
        total += last;
        order[order_index++] = 0;

        // Extract requests with a value greater than the head and calculate the requests
        last = 0;
        for (int i = 0; i < n; i++) {
            if (requests[i] > initial_head) {
                total += (requests[i] - last);
                last = requests[i];
                order[order_index++] = requests[i];
            }
        }
    }

    // Printing the order of requests in your specified format
    printf("SCAN Seek Sequence: %d", initial_head);
    for (int i = 0; i < order_index; i++) {
        printf(" -> %d", order[i]);
    }
    printf("\n");

    // Printing the total head movement
    printf("Total seek distance: %d\n", total);
}


void c_scan(int requests[], int n, int initial_head, int direction, int track_size) {
    // Sorting the requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    // Stores the order in which requests are processed
    int order[n];
    int order_index = 0;

    // Stores the total head movement
    int total = 0;

    int last = initial_head;
    
    if (direction == 1) {
        // Extract requests with a value greater than or equal to the head and calculate the requests
        for (int i = 0; i < n; i++) {
            if (requests[i] >= initial_head) {
                total += (requests[i] - last);
                last = requests[i];
                order[order_index++] = requests[i];
            }
        }
        
        // Reaching the end of the disk
        total += (track_size - last - 1);
        order[order_index++] = track_size - 1;
        
        // Reaching the starting of the disk
        total += (track_size - 1 - 0);
        order[order_index++] = 0;

        // Extract requests with a value less than the head and calculate the requests
        last = 0;
        for (int i = 0; i < n; i++) {
            if (requests[i] < initial_head) {
                total += (requests[i] - last);
                last = requests[i];
                order[order_index++] = requests[i];
            }
        }
    } else {
        // Reverse direction (left)
        // Extract requests with a value less than or equal to the head and calculate the requests
        for (int i = 0; i < n; i++) {
            if (requests[i] <= initial_head) {
                total += (last - requests[i]);
                last = requests[i];
                order[order_index++] = requests[i];
            }
        }
        
        // Reaching the starting of the disk
        total += last;
        order[order_index++] = 0;
        
        // Reaching the end of the disk
        total += track_size - 1;
        order[order_index++] = track_size - 1;

        // Extract requests with a value greater than the head and calculate the requests
        last = track_size - 1;
        for (int i = 0; i < n; i++) {
            if (requests[i] > initial_head) {
                total += (requests[i] - last);
                last = requests[i];
                order[order_index++] = requests[i];
            }
        }
    }

    // Printing the order of requests	
    printf("C-SCAN Seek Sequence: %d", initial_head);
    for (int i = 0; i < order_index; i++) {
        printf(" -> %d", order[i]);
    }
    printf("\n");
    printf("Total Seek Distance %d\n", total);
}



void look_scan(int requests[], int n, int initial_head, int direction) {
    int seek_sequence[n];
    int seek_count = 0;
    int current_head = initial_head;

    // Sort the requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }

    int start = 0;
    while (start < n && requests[start] < current_head) {
        start++;
    }

    int left = start - 1;
    int right = start;
    int i = 0;

    while (direction == 1 && right < n) {
        seek_sequence[i++] = requests[right];
        seek_count += abs(current_head - requests[right]);
        current_head = requests[right];
        right++;
    }

    while (left >= 0) {
        seek_sequence[i++] = requests[left];
        seek_count += abs(current_head - requests[left]);
        current_head = requests[left];
        left--;
    }

    printf("LOOK Seek Sequence: %d", initial_head);
    for (int i = 0; i < n; i++) {
        printf(" -> %d", seek_sequence[i]);
    }
    printf("\nTotal Seek Distance: %d\n", seek_count);
}


void c_look(int requests[], int n, int initial_head, int direction) {
    
    // Sort the requests in ascending order
    bubbleSort(requests, n);
    int seek_distance = 0;
    int current_track = initial_head;
    int next_index = 0;

    printf("C-LOOK Seek Sequence: %d", current_track);

    if (direction == 1) { // Scanning towards the end
        for (int i = 0; i < n; i++) {
            if (requests[i] >= current_track) {
                next_index = i;
                break;
            }
        }

        for (int i = next_index; i < n; i++) {
            printf(" -> %d", requests[i]);
            seek_distance += abs(requests[i] - current_track);
            current_track = requests[i];
        }

        for (int i = 0; i < next_index; i++) {
            printf(" -> %d", requests[i]);
            seek_distance += abs(requests[i] - current_track);
            current_track = requests[i];
        }
    } else { // Scanning towards the beginning
        for (int i = 0; i < n; i++) {
            if (requests[i] > current_track) {
                next_index = i;
                break;
            }
        }

        for (int i = next_index - 1; i >= 0; i--) {
            printf(" -> %d", requests[i]);
            seek_distance += abs(requests[i] - current_track);
            current_track = requests[i];
        }

        for (int i = n - 1; i >= next_index; i--) {
            printf(" -> %d", requests[i]);
            seek_distance += abs(requests[i] - current_track);
            current_track = requests[i];
        }
    }

    printf("\nTotal Seek Distance: %d\n", seek_distance);
}

void fcfs(int requests[], int n, int initial_head) {
    int seek_sequence[n];
    int seek_count = 0;
    int current_head = initial_head;

    // Start with the initial head position
    printf("FCFS Seek Sequence: %d", current_head);

    for (int i = 0; i < n; i++) {
        seek_sequence[i] = requests[i];
        seek_count += abs(current_head - requests[i]);
        current_head = requests[i];

        printf(" -> %d", seek_sequence[i]);
    }
    printf("\nTotal Seek Distance: %d\n", seek_count);
}

int main() {
    int n, initial_head, choice, track_size;
    
    printf("\nEnter the total number of tracks: ");
    scanf("%d", &track_size);
    
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int requests[n];

    printf("Enter the disk requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    while (1) {
        printf("\nDisk Scheduling Algorithms Menu\n\n");
        printf("1 - SSTF\n");
        printf("2 - SCAN\n");
        printf("3 - C-SCAN\n");
        printf("4 - LOOK\n");
        printf("5 - C-LOOK\n");
        printf("6 - FCFS\n");
        printf("7 - Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sstf(requests, n, initial_head);
                break;
            case 2:
                scan(requests, n, initial_head, -1, track_size);
                break;
            case 3:
                c_scan(requests, n, initial_head, 1, track_size);
                break;
            case 4:
                look_scan(requests, n, initial_head, 1);
                break;
            case 5:
                c_look(requests, n, initial_head, 1);
                break;
            case 6:
                fcfs(requests, n, initial_head);
                break;
            case 7:
                exit(0);
            default:
                printf("Valid menu choices [1-7]\n");
        }
    }

    return 0;
}

