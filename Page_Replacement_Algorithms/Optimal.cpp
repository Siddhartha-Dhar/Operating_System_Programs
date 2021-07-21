#include<iostream>
#include"Algorithms_Definition.cpp"
using namespace std;

//............................................................Main Function
int main(void){

    int N, fs, misses;
    cout << "\n Enter the Total Count of Page-References: ";
    cin >> N;
    cout << "\n Enter the Frame Size: ";
    cin >> fs;

    Rplc page(fs);
    cout << "\n\n Enter Page-References (Comma Seperated): ";
    page. Insert_Page(N);

    misses = page.Optimal();
    cout << "\n\n";
    page.Print_Result(03); // Print Result for Optimal thus pass 02
    cout << "\n\n Total Misses      => " << misses;
    cout << "\n Total Hits        => " << (N-misses);
    cout << "\n Page Fault Rate   => " << ((misses/(N*1.0))*100.0) << " %\n\n";

    return(0);
}