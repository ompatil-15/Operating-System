#include <stdio.h>

struct Process {
    int process_number, arrival_time, burst_time, completion_time, turnaround_time, waiting_time;
};

struct Process read(int i) {
    struct Process p;
    printf("Enter arrival time and burst time for process %d: ", i);
    scanf("%d %d", &p.arrival_time, &p.burst_time);
    p.process_number = i;
    return p;
}

int main() {
    struct Process p[10], tmp;
    float average_turnaround_time = 0, average_waiting_time = 0;
    int n, current_time = 0;

    printf("\nFCFS Scheduling Algorithm (Non-Preemptive)\n\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        p[i] = read(i + 1);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
        }
    }

    printf("\n+---------+--------------+------------+-----------------+-----------------+--------------+\n");
    printf("| Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("+---------+--------------+------------+-----------------+-----------------+--------------+\n");

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival_time) {
            current_time = p[i].arrival_time;
        }

        p[i].completion_time = current_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        average_turnaround_time += p[i].turnaround_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        average_waiting_time += p[i].waiting_time;

        printf("|    P%d   |      %2d      |     %2d     |       %2d        |       %2d        |      %2d      |\n",
               p[i].process_number, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);

        current_time = p[i].completion_time;
    }

    printf("+---------+--------------+------------+-----------------+-----------------+--------------+\n");

    average_turnaround_time /= n;
    average_waiting_time /= n;
    printf("\nAverage Turnaround Time: %.2f\n", average_turnaround_time);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);

    return 0;
}
