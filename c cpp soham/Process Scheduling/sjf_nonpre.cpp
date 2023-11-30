#include <bits/stdc++.h>
#include "TextTable.h"

using namespace std;

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compareArrivalTime(const Process &a, const Process &b)
{
    return a.arrival_time < b.arrival_time;
}

bool compareBurstTime(const Process &a, const Process &b)
{
    return a.burst_time < b.burst_time;
}

bool compareProcessID(const Process &a, const Process &b)
{
    return a.id < b.id;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for Process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    int completed = 0;

    while (completed < n)
    {
        int shortest = -1;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= currentTime && processes[i].completion_time == 0)
            {
                if (shortest == -1 || processes[i].burst_time < processes[shortest].burst_time)
                {
                    shortest = i;
                }
            }
        }

        if (shortest == -1)
        {
            currentTime++;
        }
        else
        {
            processes[shortest].completion_time = currentTime + processes[shortest].burst_time;
            processes[shortest].turnaround_time = processes[shortest].completion_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;

            currentTime = processes[shortest].completion_time;
            completed++;
        }
    }

    // Sort processes by process ID
    sort(processes.begin(), processes.end(), compareProcessID);

    // Create and display the process table
    TextTable table('-', '|', '+');
    table.add("Process ID");
    table.add("Arrival Time");
    table.add("Burst Time");
    table.add("Completion Time");
    table.add("Turnaround Time");
    table.add("Waiting Time");

    for (int i = 0; i <= n; i++)
    {
        table.endOfRow();
        table.add(to_string(processes[i].id));
        table.add(to_string(processes[i].arrival_time));
        table.add(to_string(processes[i].burst_time));
        table.add(to_string(processes[i].completion_time));
        table.add(to_string(processes[i].turnaround_time));
        table.add(to_string(processes[i].waiting_time));
    }

    cout << table << endl;

    // print average turnaround time and average waiting time
    float avg_turnaround_time = 0;
    float avg_waiting_time = 0;

    for (int i = 0; i < n; i++)
    {
        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
    }

    avg_turnaround_time /= n;
    avg_waiting_time /= n;

    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
}
