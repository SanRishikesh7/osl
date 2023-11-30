#include <bits/stdc++.h>
#include "TextTable.h"

using namespace std;

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

bool compareArrivalTime(const Process &a, const Process &b)
{
    return a.arrival_time < b.arrival_time;
}

bool comparePriority(const Process &a, const Process &b)
{
    return a.priority < b.priority;
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
        cout << "Enter priority for Process " << i + 1 << ": ";
        cin >> processes[i].priority;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    int completed = 0;

    while (completed < n)
    {
        int highestPriority = -1;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= currentTime && processes[i].completion_time == 0)
            {
                if (highestPriority == -1 || processes[i].priority < processes[highestPriority].priority)
                {
                    highestPriority = i;
                }
            }
        }

        if (highestPriority == -1)
        {
            currentTime++;
        }
        else
        {
            processes[highestPriority].completion_time = currentTime + processes[highestPriority].burst_time;
            processes[highestPriority].turnaround_time = processes[highestPriority].completion_time - processes[highestPriority].arrival_time;
            processes[highestPriority].waiting_time = processes[highestPriority].turnaround_time - processes[highestPriority].burst_time;

            currentTime = processes[highestPriority].completion_time;
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
    table.add("Priority");
    table.add("Completion Time");
    table.add("Turnaround Time");
    table.add("Waiting Time");

    for (int i = 0; i <= n; i++)
    {
        table.endOfRow();
        table.add(to_string(processes[i].id));
        table.add(to_string(processes[i].arrival_time));
        table.add(to_string(processes[i].burst_time));
        table.add(to_string(processes[i].priority));
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
