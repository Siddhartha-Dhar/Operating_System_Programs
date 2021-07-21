#include<iostream>
#include"Algorithms_Definition.cpp"
using namespace std;

//............................................................Main Function
int main(void){

    int N, fs, misses;
    cout << "\n Enter Number of Page References: ";
    cin >> N;
    cout << "\n Enter the Frame Size: ";
    cin >> fs;

    Rplc page(fs);
    cout << "\n\n Enter Page-References (Comma Seperated): ";
    page. Insert_Page(N);

    misses = page.FIFO();
    cout << "\n\n";
    page.Print_Result(01); // Print Result for FIFO thus pass 01
    cout << "\n\n Total Misses      => " << misses;
    cout << "\n Total Hits        => " << (N-misses);
    cout << "\n Page Fault Rate   => " << ((misses/(N*1.0))*100.0) << " %\n\n";

    return(0);
}