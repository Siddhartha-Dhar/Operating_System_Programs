#include "process.cpp"

//....................................Default Constructor Definition
process :: process(){
    status = false;
    PId = AT = BT = CT = TAT = WT = 0;
    Rspnc_Ratio = 0.0;
    Priority = 0;
    /*
         Lowest numbers between {1 to n} represents Highest Priority
         1 represents Highest Priority
         Initially Priority set to 0 that is (Invalid Priority) means priority not assigned
    */ 
    prev = next = NULL; // Initializing the Pointers
}
//.....................................Parameterized Constructor
process :: process(bool stat, int prcid, int Arrival, int Burst, int prio, float rsprc){
    PId = prcid;
    status = stat;
    AT = Arrival;
    BT = Burst;
    Priority = prio;
    Rspnc_Ratio = rsprc;
    CT = TAT = WT = 0;
    prev = next = NULL;
}
//............................................getStatus
bool process :: getStatus(){
    return(status);
}
//............................................getPId
int process :: getPId(){
    return(PId);
}
//............................................getAT
int process :: getAT(){
    return(AT);
}
//............................................getBT
int process :: getBT(){
    return(BT);
} 
//............................................getPriority
int process :: getPrty(){
    return(Priority);
}
//...........................................getCT
int process :: getCT(){
    return CT;
}
//...........................................getTAT
int process :: getTAT(){
    return TAT;
}
//...........................................getWT
int process :: getWT(){
    return WT;
}
//...........................................getResponseR
float process :: getRR(){
    return(Rspnc_Ratio);
}
//...........................................MantStatus
void process :: ManStatus(bool a){
    status = a;
    return;
}
//...........................................ManBTrr
/*
    Returns the left over time if any
    else 0
*/
int process :: ManBTrr(int tu){
    int temp;
    temp = BT;
    if(tu > BT){
        BT = 0;
        return(tu-temp);
    }
    else BT = (BT-tu);
    return(0);
}
//...............................................ManBT
void process :: ManBT(int val){
    BT = val;
    return;
}
//...............................................ManAT
void process :: ManAT(int val){
    AT = val;
    return;
}
//...............................................ManPId
void process :: ManPId(int val){
    PId = val;
    return;
}
//...............................................ManPrio
void process :: ManPrio(int prio){
    Priority = prio;
    return;
}
//...............................................ManRT
void process :: ManRR(float val){
    Rspnc_Ratio = val;
    return;
}
//...............................................ManCT
void process :: ManCT(int val){
    CT = val;
    return;
}
//...............................................ManTAT
void process :: ManTAT(int val){
    TAT = val;
    return;
}
//...............................................ManWT
void process :: ManWT(int val){   
    WT = val;
    return;
}
//...............................................Overload> w.r.t Priority
bool process :: operator>(process P2){
    if(Priority < P2.Priority) return true;
    else return false;
}
//...............................................Overload< w.r.t Priority
bool process :: operator<(process P2){
    if(Priority > P2.Priority) return true;
    else return false;
}
//...............................................Overload== w.r.t Priority
bool process :: operator==(process P2){
    if(Priority == P2.Priority) return true;
    else return false;
}