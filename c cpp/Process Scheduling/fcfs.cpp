#include <bits/stdc++.h>
#include "TextTable.h"

using namespace std;

struct Process
{
    int id;
    int AT;
    int BT;
    int CT;
    int TT;
    int WT;
};

bool compareProcessID(const Process &a, const Process &b)
{
    return a.id < b.id;
}

int main()
{
    int numP;
    cout << "Enter number of processes: ";
    cin >> numP;

    vector<Process> processes(numP);

    for (int i = 0; i < numP; i++)
    {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ":";
        cin >> processes[i].AT;
        cout << "Enter burst time for process " << i + 1 << ":";
        cin >> processes[i].BT;
    }

    sort(processes.begin(), processes.end(), [](Process &a, Process &b)
         { return a.AT < b.AT; });

    int currentTime = 0;
    for (int i = 0; i < numP; i++)
    {
        Process &p = processes[i];
        currentTime = max(currentTime, p.AT);
        p.CT = currentTime + p.BT;

        p.TT = p.CT - p.AT;
        p.WT = p.TT - p.BT;

        currentTime = p.CT;
    }

    // Sort processes by process ID
    sort(processes.begin(), processes.end(), compareProcessID);

    TextTable table('-', '|', '+');
    table.add("Process ID");
    table.add("Arrival Time");
    table.add("Burst Time");
    table.add("Completion Time");
    table.add("Turnaround Time");
    table.add("Waiting Time");

    for (int i = 0; i <= numP; i++)
    {
        table.endOfRow();
        table.add(to_string(processes[i].id));
        table.add(to_string(processes[i].AT));
        table.add(to_string(processes[i].BT));
        table.add(to_string(processes[i].CT));
        table.add(to_string(processes[i].TT));
        table.add(to_string(processes[i].WT));
    }
    cout << table;

    // print average turnaround time and average waiting time
    float avg_turnaround_time = 0;
    float avg_waiting_time = 0;

    for (int i = 0; i < numP; i++)
    {
        avg_turnaround_time += processes[i].TT;
        avg_waiting_time += processes[i].WT;
    }

    avg_turnaround_time /= numP;
    avg_waiting_time /= numP;

    cout << "Average Turnaround Time: " << avg_turnaround_time << endl;
    cout << "Average Waiting Time: " << avg_waiting_time << endl;
}