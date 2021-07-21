#include<iostream>
#include<cstdlib>
using namespace std;

//...............................................Menu Function
int menu(void){
    int ch;
    cout << "\n Memory Allocator";
    cout << "\n ================\n";
    cout << "\n 00. Exit";
    cout << "\n 01. First Fit";
    cout << "\n 02. Best Fit";
    cout << "\n 03. Worst Fit";
    cout << "\n 04. Performance Analyzer";

    cout << "\n\n Enter Choice ==> ";
    cin >> ch;
    getchar();
    return(ch);
}
//...............................................Main Function
int main(void){
    int choice;
    do{
        system("cls");
        choice = menu();
        switch(choice){
            case 0: // Exit
                    cout << "\n\n Exit Successfully....";
                    break;

            case 01: // First Fit
                    system("g++ First_fit.cpp -o First_fit");
                    system("First_fit.exe");
                    break;

            case 02: // Best Fit
                    system("g++ Best_fit.cpp -o Best_fit");
                    system("Best_fit.exe");
                    break;
                    
            case 03: // Worst Fit
                    system("g++ Worst_fit.cpp -o Worst_fit");
                    system("Worst_fit.exe");
                    break; 
 
            case 04: // Performance Analyzer
                    system("g++ Performance.cpp -o Performance");
                    system("Performance.exe");
                    break;
        }
        cout << "\n\n Press Enter to Continue....";
        getchar();
    }while(choice != 0);

    system("cls"); // Refresh the screen before exiting 
    return(0);
}