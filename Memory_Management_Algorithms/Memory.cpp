#include"Partition.cpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Class Definititon
class Memory{

    public:
        int N; // N is the number of partititon in Memory
        Partition *mem; // memory pointer

        Memory(int, int[]);    
        void flush_mem(void);
        bool ins_first_fit(int, int, int &);
        bool ins_best_fit(int, int, int &);
        bool ins_worst_fit(int, int, int &);
        int Callc_intrnl_frag(void);
        void Display_Allocation(void);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Function_Definitions
//............................................................Constructor
Memory :: Memory(int n, int A[]){
    N = n;
    mem = new Partition[n];
    for(int i=0; i<n; i++){
        mem[i].set_prtns(A[i]);
    }
}
//.............................................................Calculate_internal_fragmn
int Memory :: Callc_intrnl_frag(void){
    int sum = 0;
    for(int i=0; i<N; i++){
        if(mem[i].get_Allocated())
            sum += mem[i].get_intr_frgmnt();
    }
    return(sum);
}
//.............................................................flush_memory
void Memory :: flush_mem(void){
    for(int i=0; i<N; i++){
        mem[i].set_Allocated(false);
    }
    return;
}
//.............................................................ins_first_fit
/*
  return 'false' if able to allocate process
  return 'true' if the process is not allocated
*/
bool Memory :: ins_first_fit(int PId, int prcs, int &BlcId){
    for(BlcId=0; (BlcId<N)&&((mem[BlcId].get_Allocated())||(mem[BlcId].get_prtns()<prcs)); BlcId++);
    if(BlcId>=N) return(true);
    mem[BlcId].set_PId(PId);
    mem[BlcId].set_Allocated(true);
    mem[BlcId].set_prc_size(prcs);
    mem[BlcId].callc_intr_frgmnt();
    return(false);
}
//.............................................................ins_best_fit
/*
  return 'false' if able to allocate process
  return 'true' if the process is not allocated
*/
bool Memory :: ins_best_fit(int PId, int prcs, int &BlcId){
    int i, temp, t;
    bool f = false;
    BlcId = -1;
    for(i=0; i<N; i++){
        temp = ((mem[i].get_prtns())-prcs);
        if((!(mem[i].get_Allocated()))&&(temp>=0)){
            if(!f){
                t = temp;
                BlcId = i;
                f = true;
            }
            else if(temp < t){
                BlcId = i;
                t = temp;
            }
        }
    }
    if(BlcId == -1) return(true);
    mem[BlcId].set_PId(PId);
    mem[BlcId].set_Allocated(true);
    mem[BlcId].set_prc_size(prcs);
    mem[BlcId].callc_intr_frgmnt();
    return(false);
}
//..............................................................ins_worst_fit
/*
  return 'false' if able to allocate process
  return 'true' if the process is not allocated
*/
bool Memory :: ins_worst_fit(int PId, int prcs, int &BlcId){
    int i, temp, t;
    bool f = false;
    BlcId = -1;
    for(i=0; i<N; i++){
        temp = ((mem[i].get_prtns())-prcs);
        if((!(mem[i].get_Allocated()))&&(temp>=0)){
            if(!f){
                t = temp;
                BlcId = i;
                f = true;
            }
            else if(temp > t){
                BlcId = i;
                t = temp;
            }
        }
    }
    if(BlcId == -1) return(true);
    mem[BlcId].set_PId(PId);
    mem[BlcId].set_Allocated(true);
    mem[BlcId].set_prc_size(prcs);
    mem[BlcId].callc_intr_frgmnt();
    return(false);
}