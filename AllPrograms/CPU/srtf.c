#include <stdio.h>

void main()
{
    int n;
    printf("Enter No. of Processes:");
    scanf("%d", &n);

    int process[n];
    int arrival_time[n];
    int burst_time[n];
    int completion_time[n];
    int turn_around_time[n];
    int waiting_time[n];
    int response_time[n];
    int remaining_time[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter Process ID:");
        scanf("%d", &process[i]);

        printf("Enter Arrival Time:");
        scanf("%d", &arrival_time[i]);

        printf("Enter Burst Time:");
        scanf("%d", &burst_time[i]);

        remaining_time[i] = burst_time[i]; // Initialize remaining time with burst time
        printf("\n");
    }

    int time = 0;
    int completed = 0;
    int min_remaining_time_index;

    while (completed < n)
    {
        int min_remaining_time = __INT_MAX__; // Initialize with a large value

        // Find process with minimum remaining time at current time
        for (int i = 0; i < n; i++)
        {
            if (arrival_time[i] <= time && remaining_time[i] < min_remaining_time && remaining_time[i] > 0)
            {
                min_remaining_time = remaining_time[i];
                min_remaining_time_index = i;
            }
        }

        // Decrease remaining time of selected process
        remaining_time[min_remaining_time_index]--;

        // If a process is completed
        if (remaining_time[min_remaining_time_index] == 0)
        {
            completed++;
            completion_time[min_remaining_time_index] = time + 1;
            turn_around_time[min_remaining_time_index] = completion_time[min_remaining_time_index] - arrival_time[min_remaining_time_index];
            waiting_time[min_remaining_time_index] = turn_around_time[min_remaining_time_index] - burst_time[min_remaining_time_index];
            response_time[min_remaining_time_index] = waiting_time[min_remaining_time_index];
        }

        time++; // Move to next time unit
    }

    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    for (int i = 0; i < n; i++)
    {
        total_turnaround_time += turn_around_time[i];
        total_waiting_time += waiting_time[i];
    }

    float average_turnaround_time = (float)total_turnaround_time / n;
    float average_waiting_time = (float)total_waiting_time / n;

    printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", process[i], arrival_time[i], burst_time[i], completion_time[i], turn_around_time[i], waiting_time[i], response_time[i]);
    }

    printf("\n\nAverage Waiting Time:%f\tAverage Turn Around Time:%f", average_waiting_time, average_turnaround_time);
}