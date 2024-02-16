#include<iostream>
using namespace std;

void findWaitingTime(int processes[], int n, 
						int bt[], int at[], int wt[])
{
	int cur_time = 0;
	wt[0] = 0;

	for (int i = 1; i < n ; i++ )
	{
		cur_time += bt[i-1];
		wt[i] = max(0, cur_time - at[i]);
		cur_time = max(cur_time, at[i]);
	}
}

void findTurnAroundTime( int processes[], int n, 
				int bt[], int at[], int wt[], int tat[])
{
	for (int i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
}

void findavgTime( int processes[], int n, int bt[], int at[],int ct[])
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;

	findWaitingTime(processes, n, bt, at, wt);
	findTurnAroundTime(processes, n, bt, at, wt, tat);

	cout << "Processes "<< " Arrival time "<< " Burst time "<<" Completion time "
		<< " Waiting time " << " Turn around time\n";

    for (int i = 0; i < n; i++)
    {
        ct[i] = at[i] + tat[i];
    }
    
	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		cout << " " << i+1 << "\t\t" << at[i] << "\t\t " << bt[i] << "\t "<< ct[i] << "\t"
			<< wt[i] << "\t\t " << tat[i] <<endl;
	}

	cout << "Average waiting time = "
		<< (float)total_wt / (float)n;
	cout << "\nAverage turn around time = "
		<< (float)total_tat / (float)n;
}


int main()
{
	cout << "Enter the number of processes: ";
	int n;
	cin >> n;

	int processes[n], bt[n], at[n],ct[n];

	cout << "Enter the arrival time and burst time for each process:\n";
	for (int i = 0; i < n; i++)
	{
		cout << "Process " << i+1 << ":\n";
		cout << "Arrival time: ";
		cin >> at[i];
		cout << "Burst time: ";
		cin >> bt[i];
		processes[i] = i+1;
	}
	findavgTime(processes, n, bt, at,ct);
	return 0;
}