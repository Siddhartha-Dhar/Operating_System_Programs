#include<iostream>
#include"Memory.cpp"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Query Class
class Query{

    private:
        Memory *m;
    public :
        void First_fit(int[], int[], int, int);
        void Best_fit(int[], int[], int, int);
        void Worst_fit(int[], int[], int, int);
        int Performance(int[], int[], int, int);
        bool f_fit(int[], int[], int, int, int &, int &, int &);
        bool b_fit(int[], int[], int, int, int &, int &, int &);
        bool w_fit(int[], int[], int, int, int &, int &, int &);
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Function Definitions
/*
    Return 0 if any Erronous Condition appeared 
    Return 1 if First fit is best
    Return 2 if Best fit is best
    Return 3 if Worst fit is best
    Return 4 if both first fit and best fit is best
    Return 5 if both first fit and worst fit is best
    Return 6 if both best fit and worst fit is best
    Return 7 if All the three algorithms are best
*/
int Query :: Performance(int mem[], int prcs[], int ms, int ps){
    bool ff, bf, wf;
    int iff, ibf, iwf, ffnp, bfnp, wfnp, ffw, bfw, wfw;

    ff = f_fit(mem, prcs, ms, ps, iff, ffnp, ffw);
    bf = b_fit(mem, prcs, ms, ps, ibf, bfnp, bfw);
    wf = w_fit(mem, prcs, ms, ps, iwf, wfnp, wfw);

    std::cout << "\n\n                         Total-Unallocated-Process\t Total-Internal-Fragmentation\t Total-Process-Wastage";
    std::cout << "\n                         ===========================\t ============================\t =====================";
    std::cout << "\n\n First Fit Algorithm ==> \t\t" << ffnp << "\t\t\t\t" << iff << "\t\t\t" << ffw;
    std::cout << "\n\n Best Fit Algorithm  ==> \t\t" << bfnp << "\t\t\t\t" << ibf << "\t\t\t" << bfw;
    std::cout << "\n\n Worst Fit Algorithm ==> \t\t" << wfnp << "\t\t\t\t" << iwf << "\t\t\t" << wfw << "\n\n"; 

    if(ff&&bf&&wf){ // All algorithms fails to accomodate some processes

        if((ffnp==bfnp)&&(bfnp==wfnp)){  // All algorithms fails to allocate same number of processes
            
            if((ffw==bfw)&&(bfw==wfw)){ // All the algorithms done same wastage

                if((iff == ibf)&&(ibf == iwf)) return(7); // Every algorithm has same internal fragmentation thus every algorithm is best 

                if((iff<ibf)&&(iff<iwf)) return(1); // First fit's internal fragmentation is less thus it is best
                if((ibf<iff)&&(ibf<iwf)) return(2); // Best fit's internal fragmentation is less thus it is best
                if((iwf<iff)&&(iwf<ibf)) return(3); // Worst fit's internal fragmentation is less than it is best

                if((ibf<iff)&&(ibf == iwf)) return(6); // Best fit and Worst fit both has same and least internal fragmentation thus both are best
                if((iff<ibf)&&(iff == iwf)) return(5); // First fit and Worst fit both has same and least internal fragmentation thus both are best
                if((ibf<iwf)&&(ibf == iff)) return(4); // Best fit and First fit both has same and least internal fragmentation thus both are best
            } 

            if((ffw<bfw)&&(ffw<wfw)) return(1); // All algorithm misses same amount of processes and First fit has least wastage
            if((bfw<ffw)&&(bfw<wfw)) return(2); // All algorithm misses same amount of processes and Best fit has least wastage
            if((wfw<ffw)&&(wfw<bfw)) return(3); // All algorithm misses same amount of processes and Worst fit has least wastage

            if((ffw==bfw)&&(ffw<wfw)) return(4); // First fit, Best fit have same wastage but Worst fit's wastage is greater                
            if((ffw==wfw)&&(ffw<bfw)) return(5); // First fit, Worst fit have same wastage butBbest fit's wastage is greater
            if((bfw==wfw)&&(wfw<ffw)) return(6); // Best fit, Worst fit have same wastage but First fit's wastage is greater
        }
        else{ // All algorithms does not fails to allocate same number of processes
            
            if((ffnp<bfnp)&&(ffnp<wfnp)) return(1); // All algorithm misses same amount of processes and First fit has least wastage
            if((bfnp<ffnp)&&(bfnp<wfnp)) return(2); // All algorithm misses same amount of processes and Best fit has least wastage
            if((wfnp<ffnp)&&(wfnp<bfnp)) return(3); // All algorithm misses same amount of processes and Worst fit has least wastage

            if((ffnp==bfnp)&&(ffnp<wfnp)) return(4); // First fit, Best fit have same wastage but Worst fit's wastage is greater                
            if((ffnp==wfnp)&&(ffnp<bfnp)) return(5); // First fit, Worst fit have same wastage butBbest fit's wastage is greater
            if((bfnp==wfnp)&&(wfnp<ffnp)) return(6); // Best fit, Worst fit have same wastage but First fit's wastage is greater
        }
    }
    if(ff||bf||wf){ // Any one of the algorithm if fails to allocate any process
        
        if(ff){ // First fit fails to allocate at least any process

            if(bf) return(3); // Best fit fails to allocate at least any process thus worst fit must be best
            if(wf) return(2); // Worst fit fails to allocate at least any process thus best fit must be best
            if(ibf<iwf) return(2); // Internal Fragmentation of best fit is less than Worst fit thus Best fit is best
            if(iwf<ibf) return(3); // Internal Fragmentation of Worst fit is less than Best fit thus Worst fit is best
            else return(6);  // Internal Fragmentation of Best fit and Worst fit is same thus both are best
        }
        else if(bf){ // Best fit fails to allocate at least any process

            if(ff) return(3); // First fit fails to allocate at least any process thus worst fit must be best
            if(wf) return(1); // Worst fit fails to allocate at least any process thus First fit must be best
            if(iff<iwf) return(1); // Internal Fragmentation of First fit is less than Worst fit thus First fit is best
            if(iwf<iff) return(3); // Internal Fragmentation of Worst fit is less than First fit thus Worst fit is best
            else return(5);  // Internal Fragmentation of First fit and Worst fit is same thus both are best
        }
        else if(wf){ // Worst fit fails to allocate at least any process

            if(ff) return(2); // First fit fails to allocate at least any process thus Best fit must be best
            if(bf) return(1); // Best fit fails to allocate at least any process thus First fit must be best
            if(iff<ibf) return(1); // Internal Fragmentation of First fit is less than Best fit thus First fit is best
            if(ibf<iff) return(2); // Internal Fragmentation of Best fit is less than First fit thus Best fit is best
            else return(4);  // Internal Fragmentation of Best fit and First fit is same thus both are best
        }
    }
    else{ // All the algorithms successfully allocates all the processes to the Memory 

        if((iff == ibf)&&(ibf == iwf)) return(7); // Every algorithm has same internal fragmentation thus every algorithm is best 

        if((iff<ibf)&&(iff<iwf)) return(1); // First fit's internal fragmentation is less thus it is best
        if((ibf<iff)&&(ibf<iwf)) return(2); // Best fit's internal fragmentation is less thus it is best
        if((iwf<iff)&&(iwf<ibf)) return(3); // Worst fit's internal fragmentation is less than it is best

        if((ibf<iff)&&(ibf == iwf)) return(6); // Best fit and Worst fit both has same and least internal fragmentation thus both are best
        if((iff<ibf)&&(iff == iwf)) return(5); // First fit and Worst fit both has same and least internal fragmentation thus both are best
        if((ibf<iwf)&&(ibf == iff)) return(4); // Best fit and First fit both has same and least internal fragmentation thus both are best
    }
    return(0); // If any unprecedented erronous condition encountered
}
//.......................................................................................................w_fit
bool Query :: w_fit(int mem[], int prcs[], int ms, int ps, int &intr, int &nouap, int &waste){
    int BId;
    bool flag = false;
    nouap = waste = 0;
    m = new Memory(ms, mem);

    for(int i=0; i<ps; i++){
        if((m->ins_worst_fit(i, prcs[i], BId))){ //  If the process is unable to allocate memeory
            flag = true;
            nouap++;
            waste += prcs[i];
        } 
    }
    intr = m->Callc_intrnl_frag();
    return flag;
}
//.......................................................................................................b_fit
bool Query :: b_fit(int mem[], int prcs[], int ms, int ps, int &intr, int &nouap, int &waste){
    int BId;
    bool flag = false;
    nouap = waste = 0;
    m = new Memory(ms, mem);

    for(int i=0; i<ps; i++){
        if((m->ins_best_fit(i, prcs[i], BId))){ //  If the process is unable to allocate memeory
            flag = true;
            nouap++;
            waste += prcs[i];
        } 
    }
    intr = m->Callc_intrnl_frag();
    return flag;
}
//.......................................................................................................f_fit
bool Query :: f_fit(int mem[], int prcs[], int ms, int ps, int &intr, int &nouap, int &waste){
    int BId;
    bool flag = false;
    nouap = waste = 0;
    m = new Memory(ms, mem);

    for(int i=0; i<ps; i++){
        if((m->ins_first_fit(i, prcs[i], BId))){
            flag = true;
            nouap++;
            waste += prcs[i];
        }
    }
    intr = m->Callc_intrnl_frag();
    return flag;
}
//....................................................................First_fit
void Query :: First_fit(int mem[], int prcs[], int ms, int ps){
    int BId;
    m = new Memory(ms, mem);

    std::cout << "\n+---------------------------------------------------------------+";
    std::cout << "\n|  Process ID   |    Block ID   |  Used Space   |  Unused Space |";
    std::cout << "\n+---------------------------------------------------------------+";
    for(int i=0; i<ps; i++){
        if((m->ins_first_fit(i, prcs[i], BId))){ //  If the process is unable to allocate memeory
            std::cout << "\n|\t" << i+1 << "\t|\tNA\t|\tNA\t|\tNA\t|";
            std::cout << "\n+---------------------------------------------------------------+";    
        }
        else{ //  If the process has been allocated to the memory successfully
            std::cout << "\n|\t" << i+1 << "\t|\t  " << BId+1 << "\t|\t" << prcs[i] << "\t|\t" << ((m->mem[BId]).get_intr_frgmnt()) << "\t|";
            std::cout << "\n+---------------------------------------------------------------+";
        }
    }
    return;
}
//.....................................................First_fit
void Query :: Best_fit(int mem[], int prcs[], int ms, int ps){
    int BId;
    m = new Memory(ms, mem);

    std::cout << "\n+---------------------------------------------------------------+";
    std::cout << "\n|  Process ID   |    Block ID   |  Used Space   |  Unused Space |";
    std::cout << "\n+---------------------------------------------------------------+";
    for(int i=0; i<ps; i++){
        if((m->ins_best_fit(i, prcs[i], BId))){ //  If the process is unable to allocate memeory
            std::cout << "\n|\t" << i+1 << "\t|\tNA\t|\tNA\t|\tNA\t|";
            std::cout << "\n+---------------------------------------------------------------+";    
        }
        else{ //  If the process has been allocated to the memory successfully
            std::cout << "\n|\t" << i+1 << "\t|\t  " << BId+1 << "\t|\t" << prcs[i] << "\t|\t" << ((m->mem[BId]).get_intr_frgmnt()) << "\t|";
            std::cout << "\n+---------------------------------------------------------------+";

        }
    }
    return;
}
//.....................................................First_fit
void Query :: Worst_fit(int mem[], int prcs[], int ms, int ps){
    int BId;
    m = new Memory(ms, mem);

    std::cout << "\n+---------------------------------------------------------------+";
    std::cout << "\n|  Process ID   |    Block ID   |  Used Space   |  Unused Space |";
    std::cout << "\n+---------------------------------------------------------------+";
    for(int i=0; i<ps; i++){
        if((m->ins_worst_fit(i, prcs[i], BId))){ //  If the process is unable to allocate memeory
            std::cout << "\n|\t" << i+1 << "\t|\tNA\t|\tNA\t|\tNA\t|";
            std::cout << "\n+---------------------------------------------------------------+";    
        }
        else{ //  If the process has been allocated to the memory successfully
            std::cout << "\n|\t" << i+1 << "\t|\t  " << BId+1 << "\t|\t" << prcs[i] << "\t|\t" << ((m->mem[BId]).get_intr_frgmnt()) << "\t|";
            std::cout << "\n+---------------------------------------------------------------+";

        }
    }
    return;
}