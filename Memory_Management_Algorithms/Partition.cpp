//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Class_Definititon
class Partition{

    private: // private data
        int PId;
        int partn_size;
        bool Allocated;
        int process_size;
        int intrnl_frgmnt;

    public: // Public data or function elements
        Partition(void){
            PId = 0;
            Allocated = false;
        }
        Partition(int);
        int get_prtns(void);
        int get_prcs(void);
        int get_intr_frgmnt(void);        
        int get_PId(void);
        void set_prtns(int);
        void set_Allocated(bool);
        void set_prc_size(int);
        void callc_intr_frgmnt(void);
        void set_PId(int);
        bool get_Allocated();
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Function Definitions
//...................................................Constructor
Partition :: Partition(int ps){
    PId = 0;
    partn_size = ps;
    Allocated = false;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~setter methods
//..................................................set_partititons
void Partition :: set_PId(int val){
    PId = val;
    return;
}
//..................................................set_partititons
void Partition :: set_prtns(int val){
    partn_size = val;
    return;
}
//..................................................set_Allocated
void Partition :: set_Allocated(bool val){
    Allocated = val;
    return;
}
//..................................................set_process_size
void Partition :: set_prc_size(int val){
    process_size = val;
    return;
}
//..................................................Calc_intrnl_fragmnt
void Partition :: callc_intr_frgmnt(void){
    intrnl_frgmnt = (partn_size-process_size);
    return;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~getter methods
//................................................get_partition_size
int Partition :: get_PId(void){
  return(PId);
}
//................................................get_partition_size
int Partition :: get_prtns(void){
  return(partn_size);
}
//................................................get_Allocated
bool Partition :: get_Allocated(void){
    return(Allocated);
}
//................................................get_process_size
int Partition :: get_prcs(void){
    return(process_size);
}
//................................................get_intrn_frgmnt
int Partition :: get_intr_frgmnt(void){
    return(intrnl_frgmnt);
}