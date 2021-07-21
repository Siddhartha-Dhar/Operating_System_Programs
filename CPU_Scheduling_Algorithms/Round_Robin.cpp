#include<iostream>
#include<cstdlib>
#include"Scheduler_definition.cpp"

using namespace std;

//................................................................Input
void input(Scheduler &t){
    int count = 1, At, Bt, n;
    char ch;
    cout << "\n Enter total number of processes ==> ";
    cin >> n;
    getchar();
    while(n--){
        cout << "\n Enter (" << count++ << ")<==>(Arrival Time, Burst Time) ==> ";
        cin >> At >> Bt;
        getchar();
        t.insert_processes_pub(At, Bt, 1, count, 1);
    };
    return;
}
//...............................................................Main
int main(void){

    int TQ;
    Scheduler t, res;
 
    input(t);
    cout << "\n Enter the Time Quantum ==> ";
    cin >> TQ;
    getchar();

    cout << "\n\n\t\t Initially given Process Table\n";
    t.display();

    t.Round_Robin(res, TQ);

    cout << "\n\n\n\t\t Process Table after Round Robin Scheduling\n";
    res.display();
    
    cout << "\n Average Turn Around Time ===> " << res.Avg_TAT() << "\n";
    cout << "\n Average Waiting Time ===> " << res.Avg_WT() << "\n";
    cout << "\n Average Completion Time ===> " << res.Avg_CT() << "\n\n";

    return(0);
}