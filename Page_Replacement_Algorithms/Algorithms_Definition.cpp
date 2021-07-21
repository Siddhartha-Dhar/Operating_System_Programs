#include "Class_Definition.cpp"
#include<cstdlib>

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| Function for Rplc

//........................................................................................Print_Access Times
void Rplc :: Print_AT(){
    std::cout << "\n\n            Effective Access Time Report";
    std::cout << "\n ==================================================== \n";
    std::cout << "\n Effective Access Time for FIFO    ===> " << AT_FIFO;
    std::cout << "\n Effective Access Time for LRU     ===> " << AT_LRU;
    std::cout << "\n Effective Access Time for Optimal ===> " << AT_Optimal;
    std::cout << "\n\n";
    return;
}
//........................................................................................Access_Time
void Rplc :: Find_Access_Time(float Mem_AT, float Pf_T){

    float p1, p2, p3;

    f->Flush(); // Flush the Frame before Calling FIFO
    p1 = (FIFO()/(N*1.0));
    f->Flush(); // Flush the Frame before Calling LRU
    p2 = (LRU()/(N*1.0));
    f->Flush(); // Flush the Frame before Calling Optimal
    p3 = (Optimal()/(N*1.0));

    AT_FIFO = ((1.0-p1)*Mem_AT)+(p1*Pf_T);
    AT_LRU = ((1.0-p2)*Mem_AT)+(p2*Pf_T);
    AT_Optimal = ((1.0-p3)*Mem_AT)+(p3*Pf_T);
    
    return;
}
//........................................................................................Optimal
int Rplc :: Optimal(){
    
    int tmp, count;
    count = 0;

    if(Res != NULL) delete(Res);
    Res = new Result(N, Frame_Size);

    for(int i=0; i<N; i++){

        if(f->Search_Page(A[i], tmp)){ // Search for Page and Hit occurs            
            Res->Ins_Res(i, true, *f); // Updating Result Hit
            //f->Set_ST_Index(tmp, -1); // Element Hit set status to -1 so that status will be 0 at increment stage
        }
        else{ // Miss Occurs
            count++;
            if(!(f->Full_Frame())){ // Frame has space then add the Page
                f->Add_Page(A[i], -1);
                Res->Ins_Res(i, false, *f); // Updating Result Miss
            }
            else{ // Frame is Full then Replace the Page

                f->Set_ST_Optimal(A, N, i); // Set status of the Frames according to Optimal Page Replacement Strategy
                f->Page_Replace((f->Find_Max_Stat()), A[i], -1); // Replace the Oldest Page with the new one

                Res->Ins_Res(i, false, *f); // Updating Result Miss
            }
        }
        f->Incr_Stat(); //  Increment Every Status
    }
    return(count);
}
//........................................................................................LRU
int Rplc :: LRU(){
    
    int tmp, count;
    count = 0;

    if(Res != NULL) delete(Res);
    Res = new Result(N, Frame_Size);

    for(int i=0; i<N; i++){

        if(f->Search_Page(A[i], tmp)){ // Search for Page and Hit occurs            
            Res->Ins_Res(i, true, *f); // Updating Result Hit
            f->Set_ST_Index(tmp, -1); // Element Hit set status to -1 so that status will be 0 at increment stage
        }
        else{ // Miss Occurs
            count++;
            if(!(f->Full_Frame())){ // Frame has space then add the Page
                f->Add_Page(A[i], -1);
                Res->Ins_Res(i, false, *f); // Updating Result Miss
            }
            else{ // Frame is Full then Replace the Page
                f->Page_Replace((f->Find_Max_Stat()), A[i], -1); // Replace the Oldest Page with the new one
                Res->Ins_Res(i, false, *f); // Updating Result Miss
            }
        }
        f->Incr_Stat(); //  Increment Every Status
    }
    return(count);
}
//........................................................................................FIFO
int Rplc :: FIFO(){

    int tmp, count;
    count = 0;

    if(Res != NULL) delete(Res);
    Res = new Result(N, Frame_Size);

    for(int i=0; i<N; i++){

        if(f->Search_Page(A[i], tmp)){ // Search for Page and Hit occurs            
            Res->Ins_Res(i, true, *f); // Updating Result Hit
        }
        else{ // Miss Occurs
            count++;
            if(!(f->Full_Frame())){ // Frame has space then add the Page
                f->Add_Page(A[i], -1);
                Res->Ins_Res(i, false, *f); // Updating Result Miss
            }
            else{ // Frame is Full then Replace the Page
                f->Page_Replace((f->Find_Max_Stat()), A[i], -1); // Replace the Oldest Page with the new one
                Res->Ins_Res(i, false, *f); // Updating Result Miss
            }
        }
        f->Incr_Stat(); //  Increment Every Status
    }
    return(count);
}
//........................................................................................Print_Result
void Rplc :: Print_Result(int Algo){
    if(Algo == 01) std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~ FIFO ~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl; // Print FIFO
    else if(Algo == 02) std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~ LRU ~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl; // Print LRU
    else std::cout << "~~~~~~~~~~~~~~~~ Optimal Page Replacement ~~~~~~~~~~~~~~~" << std::endl;

    std::cout << "+-------------------------------------------------------+" << std::endl;
    std::cout << "|    Page-Ref   |   Hit/Miss    |   Page Frame Status   |" << std::endl;
    std::cout << "+-------------------------------------------------------+" << std::endl;
    for(int i=0; i<N; i++){
        std::cout << "|\t" << A[i] << "\t|\t";
        Res->Hit_Miss(i);
        std::cout << "\t|\t";
        Res->print_frm(i);
        std::cout << "\t|" << std::endl;
        std::cout << "+-------------------------------------------------------+" << std::endl;
    }
    return;
}
//.....................................Insert_Page
void Rplc :: Insert_Page(int n){

    if(Res != NULL) delete(Res);
    Res = new Result(n, Frame_Size);
    char ch;
    N = n;
    A = new int[n];
    for(int i=0; i<N; i++){
        std::cin >> A[i];
        getchar();
    } 
    return;
}
//.....................................Rplc
Rplc :: Rplc(int fs){

    Frame_Size = fs;
    f = new Frame(fs); // initiating the Frame Size
    Res = new Result(1, fs);
}
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| Function for Result

//...................................................Print_Frame
void Result :: print_frm(int index){
    (Val_Frm[index])->Disp_Frame();
    return;
}
//...................................................Hit_Miss
void Result :: Hit_Miss(int index){
    if(H_M[index]) std::cout << "Hit";
    else std::cout << "Miss";
    return;
}
//...................................................Ins_Res
void Result :: Ins_Res(int i, bool hm, Frame fm){
    H_M[i] = hm;
    *(Val_Frm[i]) = fm;
    return;
}
//....................................Result Constructor
Result :: Result(int n, int frs){
    N = n;
    fs = frs;
    H_M = new bool[N];
    Val_Frm = new Frame*[N];
    for(int i=0; i<N; i++) Val_Frm[i] = new Frame(frs);
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| Frame Functions

//................................................................Flush_Frame
void Frame :: Flush(){
    i = -1;
    return;
}
//................................................................Set_ST_Optimal
void Frame :: Set_ST_Optimal(int A[], int Limit, int index){
  
    for(int j=0; j<=i; j++) frm[j].Set_ST((frm[j].Get_ST())+Limit); // Set All status to max
    for(int j=0; j<=i; j++){
        bool flag = true;
        for(int k=index+1; (k<Limit)&&flag; k++){
            if(frm[j].Get_PN() == A[k]){
                frm[j].Set_ST(k);
                flag = false;
            }
        }
    }
    return;
}
//................................................................Copy by Operator Overloading
void Frame :: operator =(Frame a){
    N=a.N;
    i=a.i;
    for(int j=0; j<N; j++){
        frm[j].Set_PN(a.frm[j].Get_PN());
        frm[j].Set_ST(a.frm[j].Get_ST());
    }
    return;
}
//................................................................Find_Max_Stat
int Frame :: Find_Max_Stat(){
    int j, max, k;
    max = -1;
    for(j=0; j<=i; j++){
        if(frm[j].Get_ST() > max){
            k = j;
            max = frm[j].Get_ST();
        }
    }
    return(frm[k].Get_PN());
}
//................................................................Set_Status_Index
void Frame :: Set_ST_Index(int index, int ST){
    frm[index].Set_ST(ST);
    return;
}
//................................................................Search_Page
bool Frame :: Search_Page(int pg, int &index){
    index = -1;
    for(int j=0; j<=i; j++){
        if(frm[j].Get_PN() == pg){
            index = j;
            return(true); //  The page is present
        }
    }
    return(false);
}
//................................................................Increment_Status
void Frame :: Incr_Stat(){
    for(int j=0; j<= i; j++)
        frm[j].Set_ST(frm[j].Get_ST()+1);
    return;
}
//................................................................Page_Replace
int Frame :: Page_Replace(int target, int new_page, int status){
  
    int j;
    for(j=0; (j<N)&&((frm[j].Get_PN()) != target); j++);

    if(j==N) return(1); // When target page is not found then return 

    frm[j].Set_PN(new_page); // Replace the new_page
    frm[j].Set_ST(status);  // Set the new status
    return(0);
}
//...............................................................Disp_Frame
void Frame :: Disp_Frame(){

    for(int j=0; j<N; j++){ // Display the Frame data i.e. the Page Numbers
        if(j<i)
            std::cout << frm[j].Get_PN() << "-";
        else if(j==i)
            std::cout << frm[i].Get_PN();
        else
            std::cout << "-" << "X";
    }
    std::cout << "\t";
    return;
}
//..............................................................Add_Page Function
void Frame :: Add_Page(int PN, int ST){

    if((i+1)<=(N-1)){
        i++;
        frm[i].Set_PN(PN);
        frm[i].Set_ST(ST);
    }
    return;
}
//............................................................Full_Frame Function
bool Frame :: Full_Frame(){

    if(i==(N-1)) return(true); // When the frame is full return true
    return(false); // return false when the frame is false
}
//............................................................Constructor
Frame :: Frame(int n){
    N = n;
    i=-1; // Initialize the frame current marker;
    frm = new Block[n]; // Allocate Memory for Frame
}

//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||| Block Functions

//.......................................Get_ST
int Block :: Get_ST(){
    return(Status);
}
//.......................................Get_PN
int Block :: Get_PN(){
    return(Page_Number);
}
//.......................................Set_PN
void Block :: Set_PN(int PN){
    Page_Number = PN;
    return;
}
//.......................................Set_ST
void Block :: Set_ST(int ST){
    Status = ST;
    return;
}