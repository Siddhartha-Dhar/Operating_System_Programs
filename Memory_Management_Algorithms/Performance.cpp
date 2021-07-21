#include<iostream>
#include"Query.cpp"
#include<cstdlib>

using namespace std;

//.........................................................Input Array
void inut_arr(int n, int *A, string s){
    for(int i=0; i<n; i++){
        cout << "\n" << s;
        cin >> A[i];
        getchar();
    }
    return;
}
//.........................................................Main Function
int main(void){

    Query q;
    int m, p, *mem, *procs, choice;

    cout << "\n\tEntering Blocks";
    cout << "\n\t===============\n";
    cout << "\n Enter the total number of memory Blocks ==> ";
    cin >> m;
    getchar();
    mem = new int[m];
    inut_arr(m, mem, "Enter the Block Capacity in KB ==> ");

    cout << "\n\tEntering Processes";
    cout << "\n\t==================\n";
    cout << "\n Enter the total number of processes ==> ";
    cin >> p;
    getchar();
    procs = new int[p];
    inut_arr(p, procs, "Enter the process size in KB ==> ");

    cout << "\n\n \t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    cout << "\n \t\t\t\t\t~~~~~~~~~~~~~~ Performance Report ~~~~~~~~~~~~~~";
    cout << "\n \t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    choice = q.Performance(mem, procs, m, p); 
    cout << "\n **Note : Total-Process-Wastage is the total process sizes that remains unallocated." << endl;
    cout << "\n Report Summary ==> ";
    switch(choice){

        case 0: // Erronous Condition
                cout << " Unable to judge Performance" << endl;
                break;
        
        case 1: // First fit algorithm performs best
                cout << " First fit algorithm performs best" << endl;
                break;
        
        case 2: // Best fit algorithm performs best
                cout << " Best fit algorithm performs best" << endl;
                break;
        
        case 3: // Worst fit algorithm performs best
                cout << " Worst fit algorithm performs best" << endl;
                break;
        
        case 4: // First fit and Best fit performs best
                cout << " First fit and Best fit algorithm performs best" << endl;
                break;
        
        case 5: // First fit and Worst fit performs best
                cout << " First fit and Worst fit algorithm performs best" << endl;
                break;
        
        case 6: // Best fit and Worst fit performs best
                cout << " Best fit and Worst fit algorithm performs best" << endl;
                break;
        
        case 7: // All the algorithm performs best
                cout << " First fit, Best fit and Worst fit  algorithms performs best" << endl;
                break;
    }   
    
    return(0);
}