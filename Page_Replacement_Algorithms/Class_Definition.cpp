#include<iostream>

//.........................................................................Class Definition For Row
class Block{

    private: // Private Access Specifier Scope

        int Page_Number;
        int Status;
    
    public: // Public Access Specifier Scope

        void Set_PN(int);
        void Set_ST(int);
        int Get_PN();
        int Get_ST();
};
//.......................................................................Class Definition for Frame
class Frame{

    private: // Private Access Specifier Scope

        int N, i;
        Block *frm;

    public:
    //.......................Function Decleration
        Frame(int);
        void Flush();
        bool Full_Frame(); // 'true' when Frame is Full else returns 'false'
        void Add_Page(int, int);  // Add Block at the end of the Queue 
        void Disp_Frame(); // Display the Frame Components
        /*Returns 1 when target page is not found else 0*/
        int Page_Replace(int, int, int); // Page_Replace Fucntion
        void FIFO(int [], int); // FIFO Page Replacement Algorithm
        void Incr_Stat(); // Increment the Statuses by 1
        bool Search_Page(int, int &);
        void Set_ST_Index(int, int);
        int Find_Max_Stat(); // Return the target Page Number having maximum status
        void operator =(Frame);
        void Set_ST_Optimal(int[], int, int); // Set Status Optimal Function Sets the Status of the Frames acording to the Optimal Strategy
};
//.......................................................................Result Class
class Result{
    
    private : // Private Scope
        int N;
        int fs;
        bool *H_M; // Hit_Miss_Array if 'true' then Hit else Miss
        Frame **Val_Frm;
    
    public: // Public Scope
        Result(int, int);
        void Ins_Res(int, bool, Frame);
        void Hit_Miss(int);
        void print_frm(int);
};
//........................................................................Replace Class
class Rplc{

    private: //............Private Scope

        int Frame_Size;
        int *A=NULL;
        int N;
        float AT_FIFO, AT_LRU, AT_Optimal; // Access Time for every Algorithms
        Frame *f=NULL;
        Result *Res=NULL;

    public: //............Public Scope

        Rplc(int);
        void Insert_Page(int);
        void Print_Result(int);
        int FIFO(); // Returns the total Number of Page Faults (FIFO)
        int LRU();  // Returns the total Number of Page Faults (LRU)
        int Optimal(); // Returns the total Number of Page Faults (Optimal Page Replacement Algorithm)
        void Find_Access_Time(float, float);
        void Print_AT();
};
