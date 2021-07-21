#include<iostream>
#include"Algorithms_Definition.cpp"
using namespace std;

int main(void){

    int N, fs, misses;
    float mat, pft;
    cout << "\n Enter Number of Page References: ";
    cin >> N;
    cout << "\n Enter the Frame Size: ";
    cin >> fs;
    cout << "\n Enter Memory Access Time: ";
    cin >> mat;
    cout << "\n Enter Page-Fault Time: ";
    cin >> pft;

    Rplc page(fs);
    cout << "\n\n Enter Page-References (Comma Seperated): ";
    page. Insert_Page(N);
    page.Find_Access_Time(mat, pft);
    page.Print_AT();

    return(0);
}