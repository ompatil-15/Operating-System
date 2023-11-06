#include <stdio.h>

#define MIN_PRIORITY -9999

struct Process {
    int process_number, arrival_time, burst_time, priority, completion_time, turnaround_time, waiting_time, response_time, status;
};

struct Process read(int i) {
    struct Process p;
    printf("Enter arrival time and burst time for process %d: ", i);
    scanf("%d %d", &p.arrival_time, &p.burst_time);
    p.process_number = i;
    printf("Enter priority for process %d: ", i);
    scanf("%d", &p.priority);
    p.status = 0;
    return p;
}

int main() {
    int n, l, ct = 0, remaining;
    struct Process p[10], temp;
    float average_turnaround_time = 0, average_waiting_time = 0;

    printf("\nHighest Priority First Scheduling Algorithm\n\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        p[i] = read(i + 1);

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }

    p[9].priority = MIN_PRIORITY;
    remaining = n;

    printf("\n+---------+--------------+------------+----------+-----------------+-----------------+--------------+---------------+\n");
    printf("| Process | Arrival Time | Burst Time | Priority | Completion Time | Turnaround Time | Waiting Time | Response Time |\n");
    printf("+---------+--------------+------------+----------+-----------------+-----------------+--------------+---------------+\n");

    for (ct = p[0].arrival_time; remaining != 0;) {
        l = 9;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= ct && p[i].status != 1 && p[i].priority > p[l].priority) {
                l = i;
            }
        }

        p[l].completion_time = ct = ct + p[l].burst_time;
        p[l].turnaround_time = p[l].completion_time - p[l].arrival_time;
        average_turnaround_time += p[l].turnaround_time;
        p[l].waiting_time = p[l].turnaround_time - p[l].burst_time;
        average_waiting_time += p[l].waiting_time;
        p[l].status = 1;
        remaining--;

        printf("|    P%d   |      %2d      |     %2d     |    %2d    |       %2d        |       %2d        |      %2d      |      %2d       |\n",
               p[l].process_number, p[l].arrival_time, p[l].burst_time, p[l].priority, p[l].completion_time, p[l].turnaround_time, p[l].waiting_time, p[l].waiting_time);
    }
    printf("+---------+--------------+------------+----------+-----------------+-----------------+--------------+---------------+\n");

    average_turnaround_time /= n;
    average_waiting_time /= n;

    printf("\nAverage Turnaround Time: %.2f\n", average_turnaround_time);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);

    return 0;
}
