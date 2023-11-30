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
    for (size_t i = 0; i < refString.length(); ++i)
    {
        char page = refString[i];
        cout << "Page: " << page << endl;
        if (pageSet.find(page) != pageSet.end())
        {
            // Page Hit
            pageHits++;
        }
        else
        {
            // Page Fault
            pageFaults++;
            if (memory.size() < memSize)
            {
                // If memory is not full, simply add the page
                memory.push_back(page);
                pageSet.insert(page);
            }
            else
            {
                // If memory is full, find the page that will not be used for the longest time in the future
                char pageToRemove = '\0'; // The page to be replaced
                size_t farthestUse = 0;   // The index of the farthest use of a page
                for (char p : pageSet)
                {
                    size_t nextUse = refString.find_first_of(p, i + 1);
                    if (nextUse == string::npos)
                    {
                        pageToRemove = p;
                        break;
                    }
                    if (nextUse > farthestUse)
                    {
                        farthestUse = nextUse;
                        pageToRemove = p;
                    }
                }
                // Remove the selected page from memory and pageSet
                memory.remove(pageToRemove);
                pageSet.erase(pageToRemove);
                // Add the new page to memory and pageSet
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
