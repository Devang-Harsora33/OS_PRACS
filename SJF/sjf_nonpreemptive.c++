#include <iostream>

using namespace std;

void SJF_nonpreemptive(int ids[], int arrival_time[], int burst_time[], int n) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    int currentTime = 0;

    cout << "Process    Arrival Time    Burst Time    Waiting Time    Turnaround Time\n";

    for (int i = 0; i < n; ++i) {
        int shortest = -1;
        for (int j = 0; j < n; ++j) {
            if (arrival_time[j] <= currentTime && burst_time[j] > 0) {
                if (shortest == -1 || burst_time[j] < burst_time[shortest]) {
                    shortest = j;
                }
            }
        }
        if (shortest == -1) {
            currentTime++;
            i--;
            continue;
        }
        totalWaitingTime += currentTime - arrival_time[shortest];
        totalTurnaroundTime += currentTime + burst_time[shortest] - arrival_time[shortest];
        currentTime += burst_time[shortest];
        cout << ids[shortest] << "           " << arrival_time[shortest] << "              " << burst_time[shortest] << "              " << currentTime - arrival_time[shortest] - burst_time[shortest] << "                 " << currentTime - arrival_time[shortest] << endl;
        burst_time[shortest] = 0; // process completed
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

    cout << "Shortest Job First (Non-preemptive) Scheduling Algorithm\n\n";
    SJF_nonpreemptive(ids, arrival_time, burst_time, n);

    delete[] ids;
    delete[] arrival_time;
    delete[] burst_time;

    return 0;
}
