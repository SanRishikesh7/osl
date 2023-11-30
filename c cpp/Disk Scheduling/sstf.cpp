#include <bits/stdc++.h>
using namespace std;

int calculateSeektime(int initialHead, vector<int> diskreq)
{
    int seektime = 0;
    int currentpos = initialHead;
    int totalreq = diskreq.size();
    vector<bool> visited(totalreq, false);

    for (int i = 0; i < totalreq; i++)
    {
        int minDis = INT_MAX;
        int minIndex = -1;
        for (int j = 0; j < totalreq; j++)
        {
            if (!visited[j])
            {
                int distance = abs(diskreq[j] - currentpos);
                if (distance < minDis)
                {
                    minDis = distance;
                    minIndex = j;
                }
            }
        }
        seektime += minDis;
        currentpos = diskreq[minIndex];
        visited[minIndex] = true;
    }
    return seektime;
}

int main()
{
    int initialHead, n;
    cout << "Enter initial head pos: ";
    cin >> initialHead;

    cout << "Enter number of disk req: ";
    cin >> n;

    vector<int> diskReq(n);
    cout << "Enter disk reqs";
    for (int i = 0; i < n; i++)
    {
        cin >> diskReq[i];
    }

    int totalSeektime = calculateSeektime(initialHead, diskReq);
    cout << "Total seek time: " << totalSeektime << endl;
    return 0;
}