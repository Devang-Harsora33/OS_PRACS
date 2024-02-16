#include <stdio.h>

#define MAX_PROCESS 10

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_burst;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void round_robin(struct Process processes[], int n, int quantum) {
    int remaining_processes = n;
    int time = 0;
    int waiting_time[MAX_PROCESS] = {0};
    int turnaround_time[MAX_PROCESS] = {0};
    
    while (remaining_processes > 0) {
        for (int i = 0; i <= n; i++) {
            if (processes[i].remaining_burst > 0) {
                if (processes[i].remaining_burst > quantum) {
                    time += quantum;
                    processes[i].remaining_burst -= quantum;
                } else {
                    time += processes[i].remaining_burst;
                    processes[i].remaining_burst = 0;
                    processes[i].completion_time = time;
                    remaining_processes--;
                    turnaround_time[i] = processes[i].completion_time - processes[i].arrival_time;
                    waiting_time[i] = turnaround_time[i] - processes[i].burst_time;
                }
            }
        }
    }

    float total_waiting_time = 0, total_turnaround_time = 0;
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, waiting_time[i], turnaround_time[i]);
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main() {
    int n, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    struct Process processes[n];
    
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_burst = processes[i].burst_time;
    }

    round_robin(processes, n, quantum);

    return 0;
}
