#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

using namespace std;

int findPageFaults(vector<int> input, int capacity)
{
    unordered_set<int> s;
    unordered_map<int, int> m;

    int page_faults = 0;
    int j = 0;

    for (auto i : input)
    {
        if (s.size() < capacity)
        {
            if (s.find(i) == s.end())
            {
                s.insert(i);
                page_faults++;
            }

            m[i] = j++;
        }
        else
        {
            if (s.find(i) == s.end())
            {
                int lru = INT_MAX, val;
                for (auto it = s.begin(); it != s.end(); it++)
                {
                    if (m[*it] < lru)
                    {
                        lru = m[*it];
                        val = *it;
                    }
                }
                s.erase(val);
                s.insert(i);

                page_faults++;
            }
            m[i] = j++;
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
