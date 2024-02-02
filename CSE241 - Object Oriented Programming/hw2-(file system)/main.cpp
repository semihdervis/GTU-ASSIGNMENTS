#include <iostream>
#include <string>
#include <stdexcept>

#include "file.h"
#include "directory.h"
#include "linkedFile.h"
#include "regularFile.h"
#include "shell.h"

using namespace std;
using namespace OS;

int main() {

    Shell shell;

    cout << "myShell" << endl;
    string command;
    do {
        try {
            cout << "> ";
            cin >> command;
            if (command == "mkdir") {
                string name;
                cin >> name;
                shell.mkdir(name);
            }
            if (command == "ls") {
                if (std::cin.peek() != '\n') {
                    string flag;
                    cin >> flag;
                    if (flag == "-R") {
                        shell.lsR(&shell.getCurrent());
                    }
                }
                else shell.ls();
            }
            if (command == "cd") {
                string name;
                cin >> name;
                shell.cd(name);
            }
            if (command == "rm") {
                string name;
                cin >> name;
                shell.rm(name);
            }
            if (command == "cp") {
                string path;
                cin >> path;
                shell.cp(path);
            }
            if (command == "cat") {
                string name;
                cin >> name;
                shell.cat(name);
            }
            if (command == "link") {
                string target;
                cin >> target;
                string linkName;
                cin >> linkName;
                shell.link(target, linkName);
            }
            if (command == "touch") {
                string name;
                cin >> name;
                string data;
                cin >> data;
                shell.touch(name, data);
            }
            if (command == "ser") {
                std::ofstream outFile("disk.txt");
                shell.serializeDirectoriesToFile(&(shell.getRoot()), outFile);
            }
            if (shell.getSize() > 10000000) {
                cout << "Error: Size can't be larger than 10MB" << endl;
                return 1;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Caught exception: " << e.what() << "\n";
        }
        cout << endl;
    } while(command != "exit");

    std::ofstream outFile("disk.txt");
    shell.serializeDirectoriesToFile(&(shell.getRoot()), outFile);
    return 0;
}