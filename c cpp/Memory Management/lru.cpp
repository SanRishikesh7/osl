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
    unordered_map<char, list<char>::iterator> pageMap;

    cout << "\nPage replacement process:" << endl;
    for (char page : refString)
    {
        cout << "Page: " << page << endl;
        if (pageMap.find(page) != pageMap.end())
        {
            // Page Hit
            pageHits++;
            // Move the accessed page to the front (most recently used)
            memory.erase(pageMap[page]);
            memory.push_front(page);
            pageMap[page] = memory.begin();
        }
        else
        {
            // Page Fault
            pageFaults++;
            if (memory.size() < memSize)
            {
                // If memory is not full, simply add the page
                memory.push_front(page);
                pageMap[page] = memory.begin();
            }
            else
            {
                // If memory is full, remove the least recently used page
                char removedPage = memory.back();
                memory.pop_back();
                pageMap.erase(removedPage);
                // Add the new page to the front
                memory.push_front(page);
                pageMap[page] = memory.begin();
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
