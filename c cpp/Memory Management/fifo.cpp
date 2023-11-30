#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout << "Enter the reference string (without space): ";
    string refString;
    cin >> refString;

    cout << "Enter the Number of frames: ";
    int memSize;
    cin >> memSize;

    int pageFaults = 0;
    int pageHits = 0;
    list<char> memory;
    unordered_set<char> pageSet;

    cout << "\nPage replacement process:" << endl;
    for (char page : refString)
    {
        cout << "Page: " << page << endl;
        if (pageSet.find(page) != pageSet.end())
        {
            pageHits++;
        }
        else
        {
            pageFaults++;
            if (memory.size() < memSize)
            {
                memory.push_back(page);
                pageSet.insert(page);
            }
            else
            {
                char removedPage = memory.front();
                memory.pop_front();
                pageSet.erase(removedPage);
                memory.push_back(page);
                pageSet.insert(page);
            }
        }
        cout << "Memory state: ";
        for (char p : memory)
        {
            cout << p << " ";
        }
        cout << endl;
    }

    double pageFaultRate = static_cast<double>(pageFaults) / (pageFaults + pageHits);
    double pageHitRate = static_cast<double>(pageHits) / (pageFaults + pageHits);

    cout << "\nNumber of page faults: " << pageFaults << endl;
    cout << "Number of page hits: " << pageHits << endl;
    cout << "Page fault rate: " << pageFaultRate << endl;
    cout << "Page hit rate: " << pageHitRate << endl;

    return 0;
}
