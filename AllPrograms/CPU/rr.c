#include <stdio.h>

#define TIME_QUANTUM 2

int main()
{
    int n;
    printf("Enter No. of Processes:");
    scanf("%d", &n);

    int process[n], arrival_time[n], burst_time[n], remaining_burst_time[n], completion_time[n], turn_around_time[n], waiting_time[n], response_time[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter Process ID, Arrival Time, and Burst Time for Process %d:\n", i + 1);
        scanf("%d %d %d", &process[i], &arrival_time[i], &burst_time[i]);
        remaining_burst_time[i] = burst_time[i];
    }

    int time = 0, completed = 0, current_process = -1;

    while (completed < n)
    {
        int flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (arrival_time[i] <= time && remaining_burst_time[i] > 0)
            {
                if (current_process != i)
                {
                    if (current_process != -1)
                    {
                        remaining_burst_time[current_process] -= time - arrival_time[current_process];
                        if (remaining_burst_time[current_process] > 0) // If process hasn't completed
                            response_time[current_process] = time - arrival_time[current_process];
                        time = arrival_time[current_process];
                    }
                    current_process = i;
                    flag = 1;
                }

                int time_slice = (remaining_burst_time[current_process] <= TIME_QUANTUM) ? remaining_burst_time[current_process] : TIME_QUANTUM;
                time += time_slice;
                remaining_burst_time[current_process] -= time_slice;

                if (remaining_burst_time[current_process] == 0)
                {
                    completion_time[current_process] = time;
                    turn_around_time[current_process] = completion_time[current_process] - arrival_time[current_process];
                    waiting_time[current_process] = turn_around_time[current_process] - burst_time[current_process];
                    completed++;
                }
                flag = 1;
            }
        }
        if (flag == 0)
            time++;
    }

    int total_turnaround_time = 0, total_waiting_time = 0;

    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", process[i], arrival_time[i], burst_time[i], completion_time[i], turn_around_time[i], waiting_time[i], response_time[i]);
        total_turnaround_time += turn_around_time[i];
        total_waiting_time += waiting_time[i];
    }

    float avg_turnaround_time = (float)total_turnaround_time / n;
    float avg_waiting_time = (float)total_waiting_time / n;

    printf("\n\nAverage Waiting Time: %.2f\tAverage Turn Around Time: %.2f\n", avg_waiting_time, avg_turnaround_time);
    return 0;
}