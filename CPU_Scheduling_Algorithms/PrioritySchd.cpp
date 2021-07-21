#include<iostream>
#include<cstdlib>
#include"Scheduler_definition.cpp"

using namespace std;

//.....................................................................Input
void input(Scheduler &t){
    int count = 1, At, Bt, prt, n;
    char ch;
    cout << "\n Enter total number of processes ==> ";
    cin >> n;
    getchar();
    while(n--){
        cout << "\n Enter (" << count++ << ")<==>(Arrival Time, Priority, Burst Time) ==> ";
        cin >> At >> prt >> Bt;
        getchar();
        t.insert_processes_pub(At, Bt, prt, count, 1);
    };
    return;
}
//.....................................................................Main
int main(void){

    Scheduler t, res;

    cout << "\n\n (Smallest Number Represents Highest Priority)";
    input(t);

    cout << "\n\n\t\t Initially given Process Table\n";
    t.display();

    t.PRIORITY_SCHEDULING(res);

    cout << "\n\n\n\t\t Process Table after Priority Scheduling\n";
    res.display();

    cout << "\n Average Turn Around Time ===> " << res.Avg_TAT() << "\n";
    cout << "\n Average Waiting Time ===> " << res.Avg_WT() << "\n";
    cout << "\n Average Completion Time ===> " << res.Avg_CT() << "\n\n";       
    
    return(0);
}