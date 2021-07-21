#include<iostream>
#include"process_definition.cpp"

//...............................................................................................Scheduler Class
class Scheduler{

    private:

        int PId;       // Process ID Generator
        process *head; // Process Scheduler Head pointer
        process *tail; // Process Scheduler Tail pointer
        //........................................................Private Function
        void insert_at(process *, process *, int);
        void insert_finalPrcs(process *);
        void insert_copy(process *, Scheduler &, int);
        void Refresh_RspRto(int);
        void insert_final_srtf(Scheduler, Scheduler &, process *, int);
        void Modify_Table(int, int);
        void fetch_all_arrived(Scheduler &, int);
        bool NotEmpty();
        void Gnatt_Chart_Step(int, int);

        process * Refresh_min();
        process * insert(bool, int, int, int, int, float, int);     
        process * search(int);
        process * min_BT(int &);
        process * max_RspRt(int &);
        process * max_PRT(int &);
        process * Move(process *);
        process * Find_Potential(process *);
        process * load_to_Q(int);

    public:

        Scheduler(){       // Default Constructor
            PId = 0;
            head = NULL;
            tail = NULL;
        }
        //....................................................insert function
        int insert_processes_pub(int, int, int, float, int);
        //....................................................Scheduling Algorithms
        void FCFS(Scheduler &);
        void SJF(Scheduler &);
        void SRTF(Scheduler &);
        void HRRN(Scheduler &);
        void PRIORITY_SCHEDULING(Scheduler &);
        void Round_Robin(Scheduler &, int);
        void Multilevel_feedback_Q(Scheduler &, int, int);
        float Avg_TAT();
        float Avg_WT();
        float Avg_CT();
        //..................................................display function
        void display();
};