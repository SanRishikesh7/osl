class Node
{
public:
    int p_id;
    int arrival_time;
    int burst_time;
    int finish_time;
    int tat;
    int waiting_time;
    Node *next;

    Node(int p_id, int arrival_time, int burst_time)
    {
        this->p_id = p_id;
        this->arrival_time = arrival_time;
        this->burst_time = burst_time;
        this->finish_time = 0;
        this->tat = 0;
        this->waiting_time = 0;
        this->next = nullptr;
    }
};