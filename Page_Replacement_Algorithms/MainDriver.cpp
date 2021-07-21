/*
    Note of Caution :
    =================

    The MainDriver code will only run in Windows Kernal, As there is system called to the Kernel is involved here.
    And as a prerequisite the Host machine must have installed g++ compiler in the Operating System

    Meanwhile the System calls used can be seen in the System function argument in this code, if modified accordingly can 
    be used for other Kernals as well.
*/
#include<iostream>
#include<cstdlib>
#include"Algorithms_Definition.cpp"
using namespace std;

//............................................................Menu
int menu(void){

    int ch;
    cout << "\n Page Replacement Strategies ";
    cout << "\n =========================== \n" << endl;
    cout << " 00. Exit " << endl;
    cout << " 01. FIFO " << endl;
    cout << " 02. LRU " << endl;
    cout << " 03. Optimal Page Replacement " << endl;
    cout << " 04. Effective-Access-Time-All " << endl;
    cout << "\n\n Enter your choice ==> ";
    cin >> ch;
    getchar();
    return(ch);
}
//............................................................Main Function
int main(void){

    int choice;

    // Compile the Standalone Codes
    system("g++ FIFO.cpp -o FIFO.exe");
    system("g++ LRU.cpp -o LRU.exe");
    system("g++ Optimal.cpp -o Optimal.exe");
    system("g++ Access_Time.cpp -o Access_Time.exe");

    do{
        system("cls"); // Clear the Terminal
        choice = menu();
        switch(choice){
            case 00: // Exit
                    cout << "\n\n Exit Successfully....";
                    break;

            case 01: // FIFO
                    system("FIFO.exe");
                    break;

            case 02: // LRU
                    system("LRU.exe");
                    break;

            case 03: // Optimal
                    system("Optimal.exe");
                    break;

            case 04: // Performance
                    system("Access_Time.exe");
                    break;            
        }
        cout << "\n\n Press Enter tot Continue...";
        getchar();
    }while(choice != 0);
    
    system("cls"); // Clear the Terminal
    return(0);
}