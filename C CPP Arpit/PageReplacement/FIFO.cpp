#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

using namespace std;

int findPageFaults(vector<int> input, int capacity)
{
    unordered_set<int> s;
    queue<int> q;
    int page_faults = 0;

    for (auto i : input)
    {
        if (s.size() < capacity)
        {
            if (s.find(i) == s.end())
            {
                s.insert(i);
                q.push(i);
                page_faults++;
            }
        }
        else
        {
            if (s.find(i) == s.end())
            {
                int val = q.front();
                q.pop();

                s.erase(val);
                s.insert(i);
                q.push(i);
                page_faults++;
            }
        }
    }
    return page_faults;
}

vector<int> takeInput(const string &filename)
{
    vector<int> refString;
    ifstream stream(filename);
    string input;

    while (getline(stream, input))
    {
        istringstream iss(input);
        string temp;

        while (getline(iss, temp, ','))
        {
            refString.push_back(stoi(temp));
        }
    }

    return refString;
}

int main()
{
    vector<int> refString = takeInput("inputs/input.txt");
    int n;
    cout << "Enter capacity: ";
    cin >> n;

    cout << "No. of page faults are: " << findPageFaults(refString, n) << endl;

    return 0;
}
