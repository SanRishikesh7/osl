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
    int remaining_time;
    int response_time; // Added response time

    Process() : response_time(-1) {}
};

bool compareArrivalTime(const Process &a, const Process &b)
{
    return a.arrival_time < b.arrival_time;
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
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    int completed = 0;

    while (completed < n)
    {
        int shortest = -1;
        int shortestTime = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= currentTime && processes[i].remaining_time < shortestTime && processes[i].remaining_time > 0)
            {
                shortest = i;
                shortestTime = processes[i].remaining_time;
                if (processes[i].response_time == -1)
                    processes[i].response_time = currentTime - processes[i].arrival_time;
            }
        }

        if (shortest == -1)
        {
            currentTime++;
        }
        else
        {
            processes[shortest].remaining_time--;
            currentTime++;

            if (processes[shortest].remaining_time == 0)
            {
                completed++;
                processes[shortest].completion_time = currentTime;
                processes[shortest].turnaround_time = processes[shortest].completion_time - processes[shortest].arrival_time;
                processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
            }
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
    table.add("Response Time");

    for (int i = 0; i <= n; i++)
    {
        table.endOfRow();
        table.add(to_string(processes[i].id));
        table.add(to_string(processes[i].arrival_time));
        table.add(to_string(processes[i].burst_time));
        table.add(to_string(processes[i].completion_time));
        table.add(to_string(processes[i].turnaround_time));
        table.add(to_string(processes[i].waiting_time));
        table.add(to_string(processes[i].response_time));
    }

    cout << table << endl;

    // print average turnaround time, average waiting time, and average response time
    float avg_turnaround_time = 0;
    float avg_waiting_time = 0;
    float avg_response_time = 0;

    for (int i = 0; i < n; i++)
    {
        avg_turnaround_time += processes[i].turnaround_time;
        avg_waiting_time += processes[i].waiting_time;
        avg_response_time += processes[i].response_time;
    }

    avg_turnaround_time /= n;
    avg_waiting_time /= n;
    avg_response_time /= n;

    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
    cout << "Average Response Time: " << avg_response_time << endl;
}
