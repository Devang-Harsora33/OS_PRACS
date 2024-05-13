#include <stdio.h>

void sjfScheduling(int pid[], int at[], int bt[], int size)
{
    int ct[size], wt[size], tat[size], completed[size];
    int currentTime = 0, totalCompleted = 0;

    for (int i = 0; i < size; i++)
        completed[i] = 0;

    while (totalCompleted < size)
    {
        int minBt = __INT_MAX__, nextProcess = -1;

        for (int i = 0; i < size; i++)
        {
            if (at[i] <= currentTime && completed[i] == 0 && bt[i] < minBt)
            {
                minBt = bt[i];
                nextProcess = i;
            }
        }

        if (nextProcess == -1)
        {
            currentTime++;
            continue;
        }

        currentTime += bt[nextProcess];
        ct[nextProcess] = currentTime;
        tat[nextProcess] = ct[nextProcess] - at[nextProcess];
        wt[nextProcess] = tat[nextProcess] - bt[nextProcess];
        completed[nextProcess] = 1;
        totalCompleted++;
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < size; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        totalWaitingTime += wt[i];
        totalTurnaroundTime += tat[i];
    }
    printf("\nAverage Waiting Time: %.2f", totalWaitingTime / size);
    printf("\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime / size);
}

int main()
{
    int num_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    int pid[num_processes], at[num_processes], bt[num_processes];

    for (int i = 0; i < num_processes; i++)
    {
        printf("Enter the process %d id, arrival time, burst time: ", i + 1);
        scanf("%d %d %d", &pid[i], &at[i], &bt[i]);
    }

    sjfScheduling(pid, at, bt, num_processes);
    return 0;
}