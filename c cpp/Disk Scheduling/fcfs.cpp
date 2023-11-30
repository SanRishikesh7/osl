#include <bits/stdc++.h>
using namespace std;

int calculateSeekTime(int initialHead, vector<int> diskReq)
{
    int seekTime = 0;
    int currentPos = initialHead;
    for (int i = 0; i < diskReq.size(); i++)
    {
        seekTime += abs(diskReq[i] - currentPos);
        currentPos = diskReq[i];
    }
    return seekTime;
}

int main()
{
    int initialHead, n;
    cout << "Enteer initial head position: ";
    cin >> initialHead;

    cout << "Enter number of disk req: ";
    cin >> n;

    vector<int> diskReq(n);

    cout << "Enter disk req:";
    for (int i = 0; i < n; i++)
    {
        cin >> diskReq[i];
    }

    int totalSeektime = calculateSeekTime(initialHead, diskReq);
    cout << "totak seek time: " << totalSeektime << endl;
}