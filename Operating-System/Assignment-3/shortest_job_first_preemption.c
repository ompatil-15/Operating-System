#include <stdio.h>

struct Process {
    int process_number, arrival_time, burst_time, remaining_time, completion_time, turnaround_time, waiting_time;
};

struct Process read(int i) {
    struct Process p;
    printf("Enter arrival time and burst time for process %d: ", i);
    scanf("%d %d", &p.arrival_time, &p.burst_time);
    p.process_number = i;
    p.remaining_time = p.burst_time;
    return p;
}

int main() {
    int n, time = 0, completed = 0;
    float total_turnaround_time = 0, total_waiting_time = 0;
    struct Process processes[10], temp;

    printf("\nSJF Scheduling Algorithm (Preemptive)\n\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        processes[i] = read(i + 1);

    while (completed < n) {
        int min_burst = 9999, min_index = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time < min_burst && processes[i].remaining_time > 0) {
                min_burst = processes[i].remaining_time;
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++;
        } else {
            processes[min_index].remaining_time--;
            time++;

            if (processes[min_index].remaining_time == 0) {
                completed++;
                processes[min_index].completion_time = time;
                processes[min_index].turnaround_time = processes[min_index].completion_time - processes[min_index].arrival_time;
                processes[min_index].waiting_time = processes[min_index].turnaround_time - processes[min_index].burst_time;
                total_turnaround_time += processes[min_index].turnaround_time;
                total_waiting_time += processes[min_index].waiting_time;
            }
        }
    }

    printf("\n+---------+--------------+------------+-----------------+-----------------+--------------+\n");
    printf("| Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n");
    printf("+---------+--------------+------------+-----------------+-----------------+--------------+\n");

    for (int i = 0; i < n; i++) {
        printf("|    P%d   |      %2d      |     %2d     |       %2d        |       %2d        |      %2d      |\n",
               processes[i].process_number, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("+---------+--------------+------------+-----------------+-----------------+--------------+\n");

    float average_turnaround_time = total_turnaround_time / n;
    float average_waiting_time = total_waiting_time / n;

    printf("\nAverage Turnaround Time: %.2f\n", average_turnaround_time);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);

    return 0;
}
