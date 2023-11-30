#include <iostream>
#include <bits/stdc++.h>

// Include text table library for better O/P formatting
#include "../cpp-text-table/TextTable.h"

// Importing helpers
#include "Node.cpp"

using namespace std;

Node *HEAD = nullptr;
vector<int> GAN_CHART;

class LinkedList
{
public:
    void deleteNode(Node *node)
    {
        if (node == nullptr)
            return;

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
        if (HEAD == nullptr || node->arrival_time < HEAD->arrival_time)
        {
            node->next = HEAD;
            HEAD = node;
            return;
        }

        Node *temp = HEAD;
        while (temp != nullptr)
        {
            if (temp->next == nullptr)
            {
                temp->next = node;
                return;
            }
            else if (temp->next->arrival_time > node->arrival_time)
            {
                node->next = temp;
                temp->next = node;
                return;
            }
            else if (temp->next->arrival_time == node->arrival_time)
            {
                if (temp->next->p_id > node->p_id)
                {
                    node->next = temp;
                    temp->next = node;
                    return;
                }
                else
                {
                    node->next = temp->next->next;
                    temp->next->next = node;
                    return;
                }
            }
            temp = temp->next;
        }

        return;
    }
};

class Helper : public LinkedList
{
public:
    vector<vector<int>> split(const string &filename, char delimeter)
    {
        vector<vector<int>> tokens;
        ifstream stream(filename);
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
            cout << endl;
            tokens.push_back(temp1);
        }

        return tokens;
    }

    void takeInput()
    {
        string file_name = "inputs/input.txt";
        vector<vector<int>> tokens = split(file_name, ',');

        for (auto i : tokens)
        {
            int p_id = i[0];
            int arrival_time = i[1];
            int burst_time = i[2];
            Node *newNode = new Node(p_id, arrival_time, burst_time);
            insertNode(newNode);
        }

        return;
    }

    void calculateTime()
    {
        Node *temp = HEAD;
        int start = 0;
        while (temp != nullptr)
        {
            temp->finish_time = start + temp->burst_time;
            temp->tat = temp->finish_time - temp->arrival_time;
            temp->waiting_time = temp->tat - temp->burst_time;
            start += temp->burst_time;
            temp = temp->next;
        }

        cout << endl;
    }

    void generateGanChart()
    {
        Node *temp = HEAD;

        while (temp != nullptr)
        {
            for (int i = 0; i < temp->burst_time; i++)
            {
                GAN_CHART.push_back(temp->p_id);
            }
            temp = temp->next;
        }

        return;
    }

    vector<Node *> sortElem()
    {
        vector<Node *> nodes;
        Node *temp = HEAD;
        while (temp != nullptr)
        {
            nodes.push_back(temp);
            temp = temp->next;
        }

        sort(nodes.begin(), nodes.end(), [](const Node *a, const Node *b)
             { return a->p_id < b->p_id; });

        return nodes;
    }

    void printTable()
    {
        TextTable t('-', '|', '+');
        vector<Node *> nodes = this->sortElem();

        t.add("P_Id");
        t.add("Arrival Time");
        t.add("Burst Time");
        t.add("Finish Time");
        t.add("Turn Around Time");
        t.add("Waiting Time");
        t.endOfRow();

        for (auto i : nodes)
        {
            t.add("P" + to_string(i->p_id));
            t.add(to_string(i->arrival_time));
            t.add(to_string(i->burst_time));
            t.add(to_string(i->finish_time));
            t.add(to_string(i->tat));
            t.add(to_string(i->waiting_time));
            t.endOfRow();
        }

        t.setAlignment(6, TextTable::Alignment::RIGHT);
        cout << t;

        return;
    }

    void printGanChart()
    {
        this->generateGanChart();

        TextTable t('-', '|', '+');

        cout << "Generated gan chart is: " << endl;
        for (auto i : GAN_CHART)
        {
            t.add("P" + to_string(i));
        }
        t.endOfRow();
        t.setAlignment(6, TextTable::Alignment::LEFT);
        cout << t;
        return;
    }
};

int main()
{
    Helper helperFunctions;

    helperFunctions.takeInput();
    helperFunctions.calculateTime();
    helperFunctions.printTable();
    helperFunctions.printGanChart();
    helperFunctions.printLinkedList();
    helperFunctions.deleteLinkedList();
}