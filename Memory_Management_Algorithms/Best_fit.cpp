#include<iostream>
#include"Query.cpp"
#include<cstdlib>

using namespace std;

//................................................Input Array
void inut_arr(int n, int *A, string s){
    for(int i=0; i<n; i++){
        cout << "\n" << s;
        cin >> A[i];
        getchar();
    }
    return;
}
//................................................Main Function
int main(void){

    Query q;
    int m, p, *mem, *procs;

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
    
    q.Best_fit(mem, procs, m, p);

    return(0);
}