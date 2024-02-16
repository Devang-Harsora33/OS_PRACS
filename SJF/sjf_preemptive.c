#include <stdio.h>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_burst;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int started;
};

void SJF_preemptive(struct Process processes[], int n) {
    int time = 0, completed = 0, shortest = -1, prev_shortest = -1;
    int total_waiting_time = 0, total_turnaround_time = 0;
    
    while (completed != n) {
        shortest = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_burst > 0) {
                if (shortest == -1 || processes[i].remaining_burst < processes[shortest].remaining_burst) {
                    shortest = i;
                }
            }
        }
        
        if (shortest == -1) {
            time++;
            continue;
        }

        if (prev_shortest != shortest) {
            processes[shortest].started = time;
        }

        processes[shortest].remaining_burst--;

        if (processes[shortest].remaining_burst == 0) {
            completed++;
            processes[shortest].completion_time = time + 1;
            processes[shortest].turnaround_time = processes[shortest].completion_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
            total_waiting_time += processes[shortest].waiting_time;
            total_turnaround_time += processes[shortest].turnaround_time;
        }

        time++;
        prev_shortest = shortest;
    }

    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_burst = processes[i].burst_time;
    }

    SJF_preemptive(processes, n);

    return 0;
}
