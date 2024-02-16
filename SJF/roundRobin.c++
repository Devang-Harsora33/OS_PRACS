#include <iostream>

using namespace std;

void roundRobin(int ids[], int arrival_time[], int burst_time[], int n, int time_quantum) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int currentTime = 0;
    int remaining_time[n];

    for (int i = 0; i < n; ++i) {
        remaining_time[i] = burst_time[i];
    }

    cout << "Process    Arrival Time    Burst Time    Waiting Time    Turnaround Time\n";
    int current_process = 0;  // Index of the current process being executed
    bool completed[n] = {false};  // Array to keep track of completed processes

    while (true) {
        bool allCompleted = true;

        for (int i = 0; i < n; ++i) {
            if (remaining_time[i] > 0) {
                allCompleted = false;
                if (arrival_time[i] <= currentTime && !completed[i]) {
                    current_process = i;
                    break;
                }
            }
        }

        if (allCompleted)
            break;

        cout << ids[current_process] << "           " << arrival_time[current_process] << "              " << burst_time[current_process] << "              ";

        if (remaining_time[current_process] > time_quantum) {
            currentTime += time_quantum;
            remaining_time[current_process] -= time_quantum;
            cout << currentTime - arrival_time[current_process] - burst_time[current_process] << "                 " << currentTime - arrival_time[current_process] << endl;
        } else {
            currentTime += remaining_time[current_process];
            totalWaitingTime += currentTime - arrival_time[current_process] - burst_time[current_process];
            totalTurnaroundTime += currentTime - arrival_time[current_process];
            remaining_time[current_process] = 0;
            completed[current_process] = true;
            cout << currentTime - arrival_time[current_process] - burst_time[current_process] << "                 " << currentTime - arrival_time[current_process] << endl;
        }

        current_process = (current_process + 1) % n;  // Move to the next process
    }

    cout << "\nAverage Waiting Time: " << (double)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << (double)totalTurnaroundTime / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    int *ids = new int[n];
    int *arrival_time = new int[n];
    int *burst_time = new int[n];

    cout << "Enter process details:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Process " << i + 1 << " ID: ";
        cin >> ids[i];
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> arrival_time[i];
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> burst_time[i];
    }

    int time_quantum;
    cout << "Enter time quantum: ";
    cin >> time_quantum;

    cout << "\nRound Robin Scheduling Algorithm\n\n";
    roundRobin(ids, arrival_time, burst_time, n, time_quantum);

    delete[] ids;
    delete[] arrival_time;
    delete[] burst_time;

    return 0;
}
