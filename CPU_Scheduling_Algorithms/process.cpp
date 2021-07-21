#include<iostream>
//...............................Process Class
class process{

    private: // Private Scope

        /*
            status == False means the process is not assigned to queue now
            status == True means the process have been assigned to queue.
        */
        bool status;
        int PId; // Process ID
        int AT;  // Arrival Time
        int BT;  // Burst Time
        int Priority; // Priority
        float Rspnc_Ratio; // Response Ratio
        int CT; // Completion Time
        int TAT; // Turn Around Time
        int WT; // Waiting Time

    public: // Public Scope
        process *prev; // previous process pointer
        process *next; // Next prcoess pointer
        //..............................................................................Constructors
        process(); // Default Constructor Decleration
        process(bool, int, int, int, int, float); // Parameterized Constructor Decleration
        //...............................................................................Getters
        bool getStatus();
        int getPId();
        int getAT();
        int getBT();
        int getPrty();
        int getCT();
        int getTAT();
        int getWT();
        float getRR();
        //..............................................................................Manipulator
        void ManStatus(bool);
        void ManPId(int);
        int ManBTrr(int);
        void ManRR(float);
        void ManPrio(int);
        void ManCT(int);
        void ManTAT(int);
        void ManWT(int);
        void ManBT(int);
        void ManAT(int);        
        //..............................................................................Checkers
        bool operator>(process);
        bool operator<(process);
        bool operator==(process);
};