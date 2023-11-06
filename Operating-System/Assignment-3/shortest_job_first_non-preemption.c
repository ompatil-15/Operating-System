//SJF Scheduling Algorithm (Non-Preemptive)

#include <stdio.h>

struct Process {
    int process_number, arrival_time, burst_time, initial_time, completion_time, turnaround_time, waiting_time, response_time;
};

struct Process read(int i) {
    struct Process p;
    printf("Enter arrival time and burst time for process %d: ", i);
    scanf("%d %d", &p.arrival_time, &p.burst_time);
    p.process_number = i;
    return p;
}

int main() {
    int n, j, min = 0;
    float average_turnaround_time = 0, average_waiting_time = 0;
    struct Process processes[10], temp;

    printf("\nSJF Scheduling Algorithm (Non-Preemptive)\n\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        processes[i] = read(i + 1);

    for (int i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    for (j = 1; j < n && processes[j].arrival_time == processes[0].arrival_time; j++) {
        if (processes[j].burst_time < processes[min].burst_time) {
            min = j;
        }
    }

    temp = processes[0];
    processes[0] = processes[min];
    processes[min] = temp;
    processes[0].initial_time = processes[0].arrival_time;
    processes[0].completion_time = processes[0].initial_time + processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        for (j = i + 1, min = i; j < n && processes[j].arrival_time <= processes[i - 1].completion_time; j++) {
            if (processes[j].burst_time < processes[min].burst_time) {
                min = j;
            }
        }

        temp = processes[i];
        processes[i] = processes[min];
        processes[min] = temp;

        if (processes[i].arrival_time <= processes[i - 1].completion_time) {
            processes[i].initial_time = processes[i - 1].completion_time;
        } else {
            processes[i].initial_time = processes[i].arrival_time;
        }

        processes[i].completion_time = processes[i].initial_time + processes[i].burst_time;
    }

    printf("\n+---------+--------------+------------+-----------------+-----------------+--------------+---------------+\n");
    printf("| Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time | Response Time |");
    printf("\n+---------+--------------+------------+-----------------+-----------------+--------------+---------------+\n");

    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        average_turnaround_time += processes[i].turnaround_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        average_waiting_time += processes[i].waiting_time;

        printf("|    P%d   |      %2d      |     %2d     |       %2d        |       %2d        |      %2d      |      %2d       |\n",
               processes[i].process_number, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time, processes[i].initial_time);
    }
    printf("+---------+--------------+------------+-----------------+-----------------+--------------+---------------+\n");

    average_turnaround_time /= n;
    average_waiting_time /= n;
    printf("\nAverage Turnaround Time: %.2f\n", average_turnaround_time);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);

    return 0;
}