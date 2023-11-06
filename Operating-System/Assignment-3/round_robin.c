#include <stdio.h>

int n, q[10], front = -1, rear = -1;

struct Process {
    int process_number, arrival_time, burst_time, completion_time, turnaround_time, waiting_time, response_time, remaining_time, completed;
};

void enqueue(int i) {
    if (rear == 10)
        printf("Overflow");
    rear++;
    q[rear] = i;
    if (front == -1)
        front = 0;
}

int dequeue() {
    if (front == -1)
        printf("Underflow");
    int temp = q[front];
    if (front == rear)
        front = rear = -1;
    else
        front++;
    return temp;
}

int isInQueue(int i) {
    int k;
    for (k = front; k <= rear; k++) {
        if (q[k] == i)
            return 1;
    }
    return 0;
}

struct Process read(int i) {
    struct Process p;
     printf("Enter arrival time and burst time for process %d: ", i);
     scanf("%d %d", &p.arrival_time, &p.burst_time);
    p.process_number = i;
    p.remaining_time = p.burst_time;
    p.completed = 0;
    return p;
}

int main() {
    int i, j, tq, time = 0, remaining;
    float average_turnaround_time = 0, average_waiting_time = 0;
    struct Process p[10], temp;

    printf("\nRound Robin (Queue Implementation) Scheduling Algorithm\n\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    for (i = 0; i < n; i++)
        p[i] = read(i + 1);

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j + 1].arrival_time) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    remaining = n;
    enqueue(0);

    printf("\nSequence: ");
    for (time = p[0].arrival_time; remaining != 0;) {
        i = dequeue();
        if (p[i].remaining_time <= tq) {
            time += p[i].remaining_time;
            p[i].remaining_time = 0;
            p[i].completed = 1;
            remaining--;
            printf("-> P%d", p[i].process_number);
            p[i].completion_time = time;
            p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
            average_turnaround_time += p[i].turnaround_time;
            p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
            average_waiting_time += p[i].waiting_time;
            for (j = 0; j < n; j++) {
                if (p[j].arrival_time <= time && p[j].completed != 1 && !isInQueue(j))
                    enqueue(j);
            }
        } else {
            time += tq;
            p[i].remaining_time -= tq;
            printf("-> P%d", p[i].process_number);
            for (j = 0; j < n; j++) {
                if (p[j].arrival_time <= time && p[j].completed != 1 && i != j && !isInQueue(j))
                    enqueue(j);
            }
            enqueue(i);
        }
    }

    printf("\n\n+---------+--------------+------------+-----------------+-----------------+\n");
    printf("| Process | Arrival Time | Burst Time | Completion Time | Turnaround Time |\n");
    printf("+---------+--------------+------------+-----------------+-----------------+\n");    
    for (i = 0; i < n; i++) {
        printf("|    P%d   |      %2d      |     %2d     |       %2d        |       %2d        |\n",
               p[i].process_number, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time);
    }
    printf("+---------+--------------+------------+-----------------+-----------------+\n");

    average_turnaround_time /= n;
    average_waiting_time /= n;
    printf("\nAverage Turnaround Time: %.2f\n", average_turnaround_time);
    printf("Average Waiting Time: %.2f\n", average_waiting_time);

    return 0;
}
