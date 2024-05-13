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

    for (int i = 0; i < n; i++)
    {
        printf("Enter Process ID:");
        scanf("%d", &process[i]);

        printf("Enter Arrival Time:");
        scanf("%d", &arrival_time[i]);

        printf("Enter Burst Time:");
        scanf("%d", &burst_time[i]);

        printf("\n");
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arrival_time[j] > arrival_time[j + 1])
            {
                int temp = arrival_time[j];
                arrival_time[j] = arrival_time[j + 1];
                arrival_time[j + 1] = temp;

                temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;

                temp = burst_time[j];
                burst_time[j] = burst_time[j + 1];
                burst_time[j + 1] = temp;
            }
        }
    }

    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_completion_time = 0;

    for (int i = 0; i < n; i++)
    {
        total_completion_time += burst_time[i];
        completion_time[i] = total_completion_time;
        turn_around_time[i] = completion_time[i] - arrival_time[i];
        total_turnaround_time += turn_around_time[i];
        waiting_time[i] = turn_around_time[i] - burst_time[i];
        total_waiting_time += waiting_time[i];
        response_time[i] = waiting_time[i];
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