#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#include "../cpp-text-table/TextTable.h"
#include "Node.cpp"

vector<int> GAN_CHART;
vector<int> READY_QUEUE;
Node *HEAD = nullptr;
unordered_map<int, int> m;
int TOTAL_TIME = 0;

class LinkedList
{
public:
    void deleteNode(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        deleteNode(node->next);
        delete node;
    }

    void deleteLinkedList()
    {
        deleteNode(HEAD);
        HEAD = nullptr;
    }

    void printLinkedList()
    {
        Node *temp = HEAD;
        cout << "Ready Queue is: ";
        while (temp != nullptr)
        {
            cout << temp->p_id << " ";
            temp = temp->next;
        }
        return;
    }

protected:
    void insertNode(Node *node)
    {
        TOTAL_TIME += node->burst_time;
        if (HEAD == nullptr)
        {
            HEAD = node;
            return;
        }

        Node *temp = HEAD;

        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        temp->next = node;
        return;
    }
};

class Helper : public LinkedList
{
    vector<vector<int>> split(string &file_name, char delimeter)
    {
        vector<vector<int>> tokens;
        ifstream stream(file_name);
        string token;

        while (getline(stream, token))
        {
            istringstream iss(token);
            string temp;
            vector<int> temp1;

            while (getline(iss, temp, delimeter))
            {
                temp1.push_back(stoi(temp));
            }
            tokens.push_back(temp1);
        }

        return tokens;
    }

public:
    void takeInput()
    {
        string file_name = "inputs/input.txt";

        vector<vector<int>> tokens = split(file_name, ',');
        sort(tokens.begin(), tokens.end(), [](vector<int> a, vector<int> b)
             { return a[1] < b[1]; });

        for (auto i : tokens)
        {
            Node *newNode = new Node(i[0], i[1], i[2]);
            insertNode(newNode);
        }

        for (auto i : tokens)
        {
            m[i[0]] = i[2];
        }
    }

    void printHashMap()
    {
        for (auto i : m)
        {
            cout << i.first << " : " << i.second << endl;
        }
    }

    int checkLowestBT()
    {
        int lowestProcess = INT_MAX;
        int lowestBT = INT_MAX;

        for (auto i : READY_QUEUE)
        {
            if (m[i] < lowestBT && m[i] > 0)
            {
                lowestBT = m[i];
                lowestProcess = i;
            }
        }
        m[lowestProcess]--;

        return lowestProcess;
    }

    void printGanChart()
    {
        TextTable t('-', '|', '+');

        cout << "Generated gan chart is: " << endl;
        for (auto i : GAN_CHART)
        {
            t.add("P" + to_string(i));
        }
        t.endOfRow();
        t.setAlignment(2, TextTable::Alignment::LEFT);
        cout << t;
        return;
    }

    void printReadyQueue()
    {
        TextTable t('-', '|', '+');

        cout << "Ready Queue is: " << endl;
        for (auto i : READY_QUEUE)
        {
            t.add(to_string(i));
        }
        t.endOfRow();
        t.setAlignment(2, TextTable::Alignment::LEFT);
        cout << t;
        return;
    }

    void generateGanChart()
    {
        Node *temp = HEAD;
        int process = temp->p_id;
        for (int i = 0; i < TOTAL_TIME; i++)
        {
            if (temp != nullptr && temp->arrival_time == i)
            {
                READY_QUEUE.push_back(temp->p_id);
                temp = temp->next;
            }
            int pid = checkLowestBT();
            GAN_CHART.push_back(pid);
        }
    }

    void calculateTime()
    {
        Node *temp = HEAD;

        while (temp != nullptr)
        {
            int n = GAN_CHART.size();
            int p_id = temp->p_id;
            int finish_time = 0;
            int i = 0;
            for (i = 0; i < n; i++)
            {
                if (GAN_CHART[i] == p_id)
                {
                    finish_time = i + 1;
                }
            }
            temp->finish_time = finish_time;
            temp->tat = temp->finish_time - temp->arrival_time;
            temp->waiting_time = temp->tat - temp->burst_time;

            temp = temp->next;
        }
    }

    void printTable()
    {
        TextTable t('-', '|', '+');

        t.add("P_Id");
        t.add("Arrival Time");
        t.add("Burst Time");
        t.add("Finish Time");
        t.add("Turn Around Time");
        t.add("Waiting Time");
        t.endOfRow();

        Node *temp = HEAD;

        while (temp != nullptr)
        {
            t.add("P" + to_string(temp->p_id));
            t.add(to_string(temp->arrival_time));
            t.add(to_string(temp->burst_time));
            t.add(to_string(temp->finish_time));
            t.add(to_string(temp->tat));
            t.add(to_string(temp->waiting_time));
            t.endOfRow();

            temp = temp->next;
        }

        t.setAlignment(6, TextTable::Alignment::RIGHT);
        cout << t;

        return;
    }
};

int main()
{
    Helper help;

    help.takeInput();
    // help.printHashMap();
    // help.printLinkedList();
    help.generateGanChart();
    help.calculateTime();
    help.printTable();
    help.printGanChart();
    help.printReadyQueue();
    help.deleteLinkedList();
}
