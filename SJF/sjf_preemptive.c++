#include <iostream>

using namespace std;

void SJF_preemptive(int ids[], int arrival_time[], int burst_time[], int n) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int currentTime = 0;

    int remaining_burst_time[n];
    bool completed[n];

    for (int i = 0; i < n; ++i) {
        completed[i] = false;
        remaining_burst_time[i] = burst_time[i];
    }

    while (true) {
        int shortest = -1;
        int shortest_index = -1;
        for (int i = 0; i < n; ++i) {
            if (arrival_time[i] <= currentTime && !completed[i] && (shortest == -1 || remaining_burst_time[i] < remaining_burst_time[shortest])) {
                shortest = remaining_burst_time[i];
                shortest_index = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        if (remaining_burst_time[shortest_index] <= currentTime - arrival_time[shortest_index]) {
            totalWaitingTime += currentTime - arrival_time[shortest_index] - remaining_burst_time[shortest_index];
            currentTime += remaining_burst_time[shortest_index];
            completed[shortest_index] = true;
            remaining_burst_time[shortest_index] = 0;
            cout << ids[shortest_index] << "           " << arrival_time[shortest_index] << "              " << burst_time[shortest_index] << "              " << totalWaitingTime - burst_time[shortest_index] << "                 " << totalWaitingTime << endl;
        } else {
            totalWaitingTime += currentTime - arrival_time[shortest_index];
            currentTime += remaining_burst_time[shortest_index];
            remaining_burst_time[shortest_index] -= currentTime - arrival_time[shortest_index];
            arrival_time[shortest_index] = currentTime;
            cout << ids[shortest_index] << "           " << arrival_time[shortest_index] << "              " << burst_time[shortest_index] << "              " << totalWaitingTime - burst_time[shortest_index] << "                 " << totalWaitingTime << endl;
        }

        int count_completed = 0;
        for (int i = 0; i < n; ++i) {
            if (completed[i]) {
                count_completed++;
            }
        }

        if (count_completed == n) {
            break;
        }
    }

    cout << "\nAverage Waiting Time: " << (double)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << (double)(totalTurnaroundTime + totalWaitingTime) / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    int ids[n];
    int arrival_time[n];
    int burst_time[n];

    cout << "Enter the process id, arrival time, and burst time for each process:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Process " << i + 1 << ":\n";
        cout << "Id: ";
        cin >> ids[i];
        cout << "Arrival Time: ";
        cin >> arrival_time[i];
        cout << "Burst Time: ";
        cin >> burst_time[i];
    }

    cout << "\nShortest Job First (Preemptive) Scheduling Algorithm\n\n";
    SJF_preemptive(ids, arrival_time, burst_time, n);
    return 0;
}