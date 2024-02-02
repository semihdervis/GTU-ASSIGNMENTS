#include <iostream>
#include <string>
#include "board.h"
#include "piece.h"

using namespace std;

int main() {


    int choice;

    do {
        cout << "\nWelcome to the Chess Game!" << endl; 
        Board b;
        cout << "1- Play a new chess game\n";
        cout << "2- Load from save.txt\n";
        cout << "3- Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                b.print();
                while (!b.move()) {}
                break;
            case 2:
                b.load();
                b.print();
                while (!b.move()) {}
                break;
            case 3:
                cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }

    } while (choice != 3);

    return 0;
}