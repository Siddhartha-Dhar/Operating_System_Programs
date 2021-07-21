#include"Scheduler.cpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// inserts

//...............................................................................................Insert_Processes Public use
int Scheduler :: insert_processes_pub(int At, int Bt, int Prt, float RRn, int mode){

    process *ptr;
    ptr = insert(false, ++PId, At, Bt, Prt, RRn, mode);

    if(ptr == NULL) return(1); // Unsuccessfull Process Creation
    return(0);  // Successfull Process Creation
}

//...............................................................................................Insert_Final_SRTF
void Scheduler :: insert_final_srtf(Scheduler origin, Scheduler &f, process *p, int Time){

    process *ptr;
    int AT, BT;

    ptr = origin.search((p->getPId()));
    if(ptr == NULL) return;

    (p->ManCT(Time));
    AT = (ptr->getAT());
    BT = (ptr->getBT());
    (p->ManAT(AT));
    (p->ManBT(BT));
    (p->ManTAT((p->getCT())-AT));
    (p->ManWT((p->getTAT())-BT));

    f.insert_finalPrcs(Move(p));

    return;
}
//...............................................................................................insert_copy
void Scheduler :: insert_copy(process *p, Scheduler &f, int mode){

    f.insert(false, (p->getPId()), (p->getAT()), (p->getBT()), (p->getPrty()), (p->getRR()), mode);
    return;
}
//................................................................................................insert
/*
    Returns 1 if unable to allocate memory
    else 0

    mode == 0 when Arrival Time is same then store shortest job first
    mode == 1 when Arrival Time is same then store Highest Priority first
*/
process* Scheduler :: insert(bool stat, int PId, int at, int bt, int prio, float rr, int mode){

    process *ptr = new process(stat, PId, at, bt, prio, rr);

    if(ptr == NULL) return NULL;

    if( head == NULL ){
        head = ptr;
        tail = ptr;
    }    
    else{
        process *pptr;
        for(pptr = head; pptr != NULL; pptr=(pptr->next)){
            if((ptr->getAT())<(pptr->getAT())){   //..........new process has less AT
                insert_at(pptr, ptr, 0);
                return(0);
            }
            else if((ptr->getAT())==(pptr->getAT())){ //......When Arrival Time is Same

                if((mode == 0)&&(ptr->getBT())<(pptr->getBT())){ // Store shortest Burst Time first
                    insert_at(pptr, ptr, 0);
                    return(0);
                }
                else if((mode == 0)&&((ptr->getBT())==(pptr->getBT()))&&((ptr->getPId())<(pptr->getPId()))){ // Arrival Time Same, Burst Time Same, break tie by PId
                    insert_at(pptr, ptr, 0);
                    return(0);
                }
                else if((mode==1)&&(*ptr > *pptr)){ // Note that '>' is overloaded in process class // Store Highest Priority first
                    insert_at(pptr, ptr, 0);
                    return(0);
                }
                else if((mode == 1)&&(*ptr==*pptr)&&((ptr->getPId())<(pptr->getPId()))){ // Arrival Time Same, Priority Same then break tie by PId
                    insert_at(pptr, ptr, 0);
                    return(0);
                }
            }
        }
        insert_at(tail, ptr, 1);
    }
    return(ptr);
}
//................................................................................................insert_prcs_obj
void Scheduler :: insert_finalPrcs(process *p){

    if(head == NULL){
        head = p;
        tail = p;
        (p->next) = (p->prev) = NULL;
    }
    else{
        process *ptr = head;
        (p->prev) = (ptr->prev);
        (p->next) = ptr;
        (ptr->prev) = p;
        head = p;
    }    
    return;
}
//................................................................................................insert_at
/*
    mode == 0 insert src at begining of dest
    mode == 1 insert src at end of dest
*/
void Scheduler :: insert_at(process *dest, process *src, int mode){

    (src->prev) = (src->next) = NULL;
    if( dest == NULL ){ // src is the first node
        head = src;
        tail = src;
    }
    else{
        if(mode == 0){ // beginning
            (src->next) = dest;
            if(dest->prev == NULL) head = src;
            else{
                (src->prev) = (dest->prev);
                ((src->prev)->next) = src;
            }
            (dest->prev) = src;
        }
        else{ // end
            (src->prev) = dest;
            if(dest->next == NULL) tail = src;
            else{
                (src->next) = (dest->next);
                ((src->next)->prev) = src;
            }
            (dest->next) = src;
        }
    }
    return;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Utilities

//...............................................................................................Find_Potential
process* Scheduler :: Find_Potential(process *p){

    process *ptr;
    if(p==NULL) return NULL;
    for(ptr=p; (ptr != NULL)&&((ptr->getAT())==(p->getAT())); ptr=(ptr->next));
    return ptr;
}
//...............................................................................................Search w.r.t PId
process * Scheduler :: search(int PId){
    process *ptr;
    for(ptr = head; ptr != NULL; ptr=(ptr->next)){
        if((ptr->getPId())==PId) return ptr;
    }
    return NULL;
}
//................................................................................................max_PRTY
process * Scheduler :: max_PRT(int &Time){
    
    process *ptr, *m;
    int temp;
    if(head==NULL) return NULL;
    m = head;
    if((m->getAT())>Time){
        temp = Time;
        Time = (m->getAT());
        std::cout << "[ CPU Idle "<<(Time-temp)<<"]=="<< Time << "==>"; // printing the CPU idle time for Priority Scheduling
    }
    for(ptr = head; ptr != NULL; ptr = (ptr->next)){
        if( ((ptr->getAT()) <= Time) && ((*ptr)>(*m)) ){
            m = ptr;
        }
    }
    return m;
}
//................................................................................................min_BT
process * Scheduler :: min_BT(int &Time){

    process *ptr, *m;

    int temp;
    if(head==NULL) return NULL;
    m = head;
    if((m->getAT())>Time){
        temp = Time;
        Time = (m->getAT());
        std::cout << "[ CPU Idle "<<(Time-temp)<<"]=="<< Time << "==>"; // Printing the CPU idle duration in SJF
    }
    for(ptr = head; ptr != NULL; ptr = (ptr->next)){
        if( ((ptr->getAT()) <= Time) && ((ptr->getBT())<(m->getBT())) ){
            m = ptr;
        }
    }
    return m;
}
//................................................................................................Move
process * Scheduler :: Move(process *p){
    if((p->prev)==NULL){ // Move first node or the only node
        head = (p->next);
        if((p->next)==NULL) tail = NULL;
        else ((p->next)->prev) = NULL;
    }
    else if((p->next)==NULL){ // Move the last node
        tail = (p->prev);
        ((p->prev)->next) = NULL;
    }
    else{ // In between node
        ((p->prev)->next) = (p->next);
        ((p->next)->prev) = (p->prev);
    }
    return p;
}
//................................................................................................Refresh_min
process * Scheduler :: Refresh_min(){

    process *ptr, *m;
    m = NULL;
    for(ptr = head; ptr!=NULL; ptr=(ptr->next)){
        if((ptr->getStatus())!=true){
            if((m==NULL)||((ptr->getPId())<(m->getPId()))) 
                m = ptr;
        }
    }
    return m;
} 
//................................................................................................display
void Scheduler :: display(void){

    process *ptr;
    std::cout << "+-----------------------------------------------------------------------------------------------+" << std::endl;
    std::cout << "|   PId   |   Arrival   |   Burst   |  Priority  |  Completion  |  Turn Around  |    Waiting    |" << std::endl;
    std::cout << "+-----------------------------------------------------------------------------------------------+" << std::endl;
    ptr = Refresh_min();
    while(ptr != NULL){

        (ptr->ManStatus(true));
        std::cout << "|   " << (ptr->getPId()) << "\t\t";
        std::cout << (ptr->getAT()) << "\t    ";
        std::cout << (ptr->getBT()) << "\t\t  ";
        std::cout << (ptr->getPrty()) << "\t\t";
        std::cout << (ptr->getCT()) << "\t\t";
        std::cout << (ptr->getTAT()) << "\t\t";
        std::cout << (ptr->getWT()) << "\t|"<< std::endl;
        std::cout << "+-----------------------------------------------------------------------------------------------+" << std::endl;
        ptr=Refresh_min();
    }
    for(ptr=head; ptr!=NULL; ptr=(ptr->next)) (ptr->ManStatus(false));
    return;
}
//................................................................................................Modify_Table
void Scheduler :: Modify_Table(int modify_at, int tu){

    process *ptr, *pptr;
    ptr = head;
    while((ptr != NULL)&&((ptr->getAT())==modify_at)){
        ptr = Move(ptr);
        (ptr->ManAT((ptr->getAT())+tu));
        insert(false, (ptr->getPId()), (ptr->getAT()), (ptr->getBT()), (ptr->getPrty()), (ptr->getRR()), 0);
        pptr = ptr;
        ptr = (ptr->next);
        free(pptr);
    }
    return;
}
//..............................................................................................Refresh_RspRto
void Scheduler :: Refresh_RspRto(int Time){

    int wt, at, bt;
    process *ptr;
    for(ptr = head; ptr != NULL; ptr=(ptr->next)){
        at = (ptr->getAT());
        bt = (ptr->getBT());
        wt = (Time - at);
        (ptr->ManRR( (wt+bt)/(bt*1.0) ));
    }
    return;
}
//............................................................................................max_RspRt
process * Scheduler :: max_RspRt(int &Time){

    process *ptr, *m;
    int temp;
    if(head==NULL) return NULL;
    m = head;
    if((m->getAT())>Time){
        temp = Time;
        Time = (m->getAT());
        std::cout << "[ CPU Idle "<<(Time-temp)<<"]=="<< Time << "==>";
    }
    for(ptr = head; ptr != NULL; ptr = (ptr->next)){
        if( ((ptr->getAT()) <= Time) && ((ptr->getRR())>(m->getRR())) ){
            m = ptr;
        }
    }
    return m;
}
//...............................................................................................load_to_Q
process * Scheduler :: load_to_Q(int Time){

    process *ptr;
    for(ptr=head; ptr!=NULL; ptr=(ptr->next)){
        if((ptr->getAT())<=Time){
            Move(ptr);
            return(ptr);
        }
    }
    return NULL;
}
//...............................................................................................fetch_all_arrived
void Scheduler :: fetch_all_arrived(Scheduler &t, int Time){

    process *ptr;
    ptr = t.load_to_Q(Time);

    while(ptr != NULL){
        insert_at(tail, ptr, 1);
        ptr = t.load_to_Q(Time);
    }   
    return;
}
//...............................................................................................IsEmpty
bool Scheduler :: NotEmpty(){
    if(head==NULL) return false;
    return true;
}
//...............................................................................................Avg_TAT
float Scheduler :: Avg_TAT(){

    float temp, count;
    process *ptr;
    temp = 0;
    count = 1;
    for(ptr=head; ptr!=NULL; ptr=(ptr->next)){
        temp=(temp+(ptr->getTAT()));
        count++;
    }
    return (temp/--count);
}
//...............................................................................................Avg_WT
float Scheduler :: Avg_WT(){

    float temp, count;
    process *ptr;
    temp = 0;
    count = 1;
    for(ptr=head; ptr!=NULL; ptr=(ptr->next)){
        temp=(temp+(ptr->getWT()));
        count++;
    }
    return (temp/--count);
}
//...............................................................................................Avg_CT
float Scheduler :: Avg_CT(){

    float temp, count;
    process *ptr;
    temp = 0;
    count = 1;
    for(ptr=head; ptr!=NULL; ptr=(ptr->next)){
        temp=(temp+(ptr->getCT()));
        count++;
    }
    return (temp/--count);
}
//.............................................................................................Gnatt_Chart_Step
void Scheduler :: Gnatt_Chart_Step(int PId, int Run){
    std::cout << "[P" << PId << "]==" << Run << "==>";
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// CPU Schedulings

//...............................................................................................Multilevel_feedback_Q
void Scheduler :: Multilevel_feedback_Q(Scheduler &f, int Q1_tq, int Q2_tq){

    process *ptr, *p;
    Scheduler Original, Q1, Q2, Q3;
    int Time=0, left_over, temp;

    // Q1_tq is the Time Quantum for the First Queue
    // Q2_tq is the Time Quantum for the Second Queue

    for(ptr = head; ptr != NULL; ptr = (ptr->next)){ // Copying the Scheduler table to Original
        insert_copy(ptr, Original, 0);
    }

    if(head != NULL) Time = (head->getAT());
    std::cout << "\n\n Gnatt Chart ==> " << Time << "===>";

    Q1.fetch_all_arrived(*this, Time); // Schedule the first process to Q1

    while((head != NULL)||(Q1.NotEmpty())||(Q2.NotEmpty())||(Q3.NotEmpty())){ // If any process left then repeat

        Q1.fetch_all_arrived(*this, Time); // Check whether any new process appeared or not if so send it to Q1

        if(Q1.NotEmpty()){ // If Q1 is not empty then do the Q1

            left_over = ((Q1.head)->ManBTrr(Q1_tq)); // Pick_Up the 
            Time = (Time + (Q1_tq - left_over));
            ptr = Q1.Move(Q1.head);
            Gnatt_Chart_Step((ptr->getPId()), Time);

            if((ptr->getBT())==0){ // The process is finished
                p = (Original.search(ptr->getPId()));
                (ptr->ManBT(p->getBT()));
                (ptr->ManCT(Time)); // Calculating the Completion TIme
                (ptr->ManTAT((ptr->getCT())-(ptr->getAT()))); // Calculating the Turnaround Time
                (ptr->ManWT((ptr->getTAT())-(ptr->getBT()))); // Calculating the Waiting Time
                f.insert_finalPrcs(ptr); // Insert the process to Final result
            }
            else{ // The process does not finished within the Time Quantum then Shift it to Q2            
                Q2.insert_at(Q2.tail, ptr, 1); // Inserting at end of Q2
            }
        }
        else if(Q2.NotEmpty()){ // If Q1 is empty and Q2 in not empty then proceed with Q2
            
            left_over = ((Q2.head)->ManBTrr(Q2_tq)); // Pick_Up the 
            Time = (Time + (Q2_tq - left_over));
            ptr = Q2.Move(Q2.head);
            Gnatt_Chart_Step((ptr->getPId()), Time);

            if((ptr->getBT())==0){ // The process is finished
                p = (Original.search(ptr->getPId()));
                (ptr->ManBT(p->getBT()));
                (ptr->ManCT(Time)); // Calculating the Completion TIme
                (ptr->ManTAT((ptr->getCT())-(ptr->getAT()))); // Calculating the Turnaround Time
                (ptr->ManWT((ptr->getTAT())-(ptr->getBT()))); // Calculating the Waiting Time
                f.insert_finalPrcs(ptr); // Insert the process to Final result
            }
            else{ // The process does not finished within the Time Quantum then Shift it to Q3
                Q3.insert_at(Q3.tail, ptr, 1); // Inserting at end of Q3
            }
        }
        else if(Q3.NotEmpty()){ // If Q1 and Q2 are empty then proceed with Q3 

            ptr = Q3.Move(Q3.head);
            Time = (Time + (ptr->getBT()));
            Gnatt_Chart_Step((ptr->getPId()), Time);
            p = (Original.search(ptr->getPId()));
            (ptr->ManBT(p->getBT()));
            (ptr->ManCT(Time)); // Calculating the Completion TIme
            (ptr->ManTAT((ptr->getCT())-(ptr->getAT()))); // Calculating the Turnaround Time
            (ptr->ManWT((ptr->getTAT())-(ptr->getBT()))); // Calculating the Waiting Time
            f.insert_finalPrcs(ptr); // Insert the process to Final result
        }
        else if(head != NULL){ // else signifies all the three Queues are empty but still have unarrived processes, then take that process and set Time
            temp = Time;
            Time = (head->getAT());
            std::cout << "[ CPU Idle "<<(Time-temp)<<"]=="<< Time << "==>";
        }
    }
    std::cout << "[End]";
    return;
}
//...............................................................................................Round_Robin
void Scheduler :: Round_Robin(Scheduler &f, int timeq){

    int Time = 0, left_over, temp;
    process *p, *pptr;
    Scheduler Unallocated, Original;

    p=head;
    if(head!=NULL) Time = (p->getAT());
    std::cout << "\n\n Gnatt Chart ==> " << Time << "===>";

    while(p != NULL){ // Copying the Scheduer table to Original
        insert_copy(p, Original, 1);
        insert_copy(p, Unallocated, 1);
        pptr = p;
        p=(p->next);
        Move(pptr);
        free(pptr);
    }

    fetch_all_arrived(Unallocated, Time);
    p=head;

    while((p!=NULL)||Unallocated.NotEmpty()){
        fetch_all_arrived(Unallocated, Time);
        p=head;
        if(p!=NULL){ // Q is non empty thus go with the processes that had been allocated
            left_over = (p->ManBTrr(timeq));
            Time = (Time + (timeq-left_over));
            Gnatt_Chart_Step((p->getPId()), Time);
            if((p->getBT())==0){ // Process Completed Store it to f
                pptr = Original.search(p->getPId());
                (p->ManBT(pptr->getBT()));
                (p->ManCT(Time));
                (p->ManTAT((p->getCT())-(p->getAT()))); // Calculating TAT
                (p->ManWT((p->getTAT())-(p->getBT()))); // Calculating TAT
                f.insert_finalPrcs(Move(p));
                fetch_all_arrived(Unallocated, Time);
            }
            else{ // Re insert the process at the end of Q
                Move(p);
                fetch_all_arrived(Unallocated, Time);
                insert_at(tail, p, 1);
            }
            p=head;
        }
        else if(Unallocated.NotEmpty()){ // Q empty but some processes remains to get allocated
            temp = Time;
            Time = ((Unallocated.head)->getAT());
            std::cout << "[ CPU Idle "<<(Time-temp)<<"]=="<< Time << "==>";        
        }
    }
    std::cout << "[End]";
    return;
}
//...............................................................................................................SRTF
void Scheduler :: SRTF(Scheduler &f){

    int tu, Time, modify_at;
    Scheduler Original;
    process *p, *pp;

    for(p = head; p != NULL; p=(p->next)){ // Copying the Scheduler table to Original
        insert_copy(p, Original, 0);
    }

    p = head;
    Time = (p->getAT()); // Setting the Time initially 
    std::cout << "\n\n Gnatt Chart ==> " << Time << "===>";

    while(p != NULL){

        pp = Find_Potential(p);  // Find the Potential Process

        if( pp != NULL ){  // pp exists
            tu = ((pp->getAT())-(p->getAT()));
        }
        else{   // pp doesnt exists

            tu = (p->getBT());
        }
        if(tu < (p->getBT()) ){ // Available Time is within Reach

            (p->ManBT((p->getBT())-tu));
            Time = (Time + tu);
            Gnatt_Chart_Step((p->getPId()), Time); // Printing Gnatt Chart Step
            modify_at = (p->getAT()); // Modify the AT of those processes who have AT == modify_at
        }
        else{ // Available Time is more than Burst time, Burst is zero
            tu = (p->getBT());
            Time = (Time + tu);
            modify_at = (p->getAT()); // Modify the AT of those processes who have AT == modify_at
            Gnatt_Chart_Step((p->getPId()), Time); // Printing Gnatt Chart Step
            insert_final_srtf(Original, f, p,Time);
        }
        Modify_Table(modify_at, tu);
        p = head;
    }
    std::cout << "[End]";
    return;
}
//...............................................................................................HRRN
void Scheduler :: HRRN(Scheduler &f){

    int Time = 0;
    process *ptr;

    Time = (head->getAT());
    ptr = head;
    std::cout << "\n\n Gnatt Chart ==> " << Time << "===>";  
    while(ptr != NULL){
            
        Time = (Time + (ptr->getBT()));

        (ptr->ManCT(Time));
        (ptr->ManTAT((ptr->getCT())-(ptr->getAT())));
        (ptr->ManWT((ptr->getTAT())-(ptr->getBT())));

        Gnatt_Chart_Step((ptr->getPId()), Time); // For Printing the Gnatt Chart Step by Step
        f.insert_finalPrcs(Move(ptr));  

        Refresh_RspRto(Time);

        ptr = max_RspRt(Time);
    }
    std::cout << "[End]";
    return;    
}
//................................................................................................PRIORITY_SCHEDULING
void Scheduler :: PRIORITY_SCHEDULING(Scheduler &f){

    int Time = 0;
    process *ptr;

    Time = (head->getAT());
    ptr = head;
    std::cout << "\n\n Gnatt Chart ==> " << Time << "===>";
    while(ptr != NULL){
            
        Time = (Time + (ptr->getBT()));

        (ptr->ManCT(Time));
        (ptr->ManTAT((ptr->getCT())-(ptr->getAT())));
        (ptr->ManWT((ptr->getTAT())-(ptr->getBT())));

        Gnatt_Chart_Step((ptr->getPId()), Time); // For Printing the Gnatt Chart Step by Step
        f.insert_finalPrcs(Move(ptr));  

        ptr = max_PRT(Time);
    }
    std::cout << "[End]";
    return;
}
//................................................................................................SJF
void Scheduler :: SJF(Scheduler &f){

    int Time = 0;
    process *ptr;

    Time = (head->getAT());
    ptr = head;
    std::cout << "\n\n Gnatt Chart ==> " << Time << "===>";
    while(ptr != NULL){
            
        Time = (Time + (ptr->getBT()));

        (ptr->ManCT(Time));
        (ptr->ManTAT((ptr->getCT())-(ptr->getAT())));
        (ptr->ManWT((ptr->getTAT())-(ptr->getBT())));
 
        Gnatt_Chart_Step((ptr->getPId()), Time); // For Printing the Gnatt Chart Step by Step
        f.insert_finalPrcs(Move(ptr));  

        ptr = min_BT(Time);
    }
    std::cout << "[End]";
    return;
}
//................................................................................................FCFS
void Scheduler :: FCFS(Scheduler &f){

    int Time, temp;
    bool entry = false;
    process *ptr, *pptr;

    Time = 0;
    Time = (head->getAT());
    ptr = head;
    std::cout << "\n\n Gnatt Chart ==> " << Time << "===>";
    while(ptr != NULL){

        if(entry&&((ptr->getAT())>Time)){
            temp = Time;
            Time = (ptr->getAT());
            std::cout << "[ CPU Idle "<<(Time-temp)<<"]=="<< Time << "==>";
        }    
        Time = (Time + (ptr->getBT()));

        (ptr->ManCT(Time));
        (ptr->ManTAT((ptr->getCT())-(ptr->getAT())));
        (ptr->ManWT((ptr->getTAT())-(ptr->getBT())));
        
        entry = true;
        pptr = ptr;
        ptr=(ptr->next);
        Gnatt_Chart_Step((pptr->getPId()), Time); // For Printing the Gnatt Chart Step by Step
        f.insert_finalPrcs(Move(pptr));
    }
    std::cout <<"[End]";
    return;
}