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
//.................................................................Main
int main(void){

    Scheduler t, res;
    input(t);

    cout << "\n\n\t\t Initially given Process Table\n";
    t.display();

    // Let Time Quantum for the first Queue Q1 is 4
    // Let Time Quantum for the second Queue Q2 is 8 
    t.Multilevel_feedback_Q(res, 4, 8);

    cout << "\n\n\n\t\t Process Table after Multilevel Feedback Queue Scheduling\n";
    res.display();
    
    cout << "\n Average Turn Around Time ===> " << res.Avg_TAT() << "\n";
    cout << "\n Average Waiting Time ===> " << res.Avg_WT() << "\n";
    cout << "\n Average Completion Time ===> " << res.Avg_CT() << "\n\n";

    return(0);
}