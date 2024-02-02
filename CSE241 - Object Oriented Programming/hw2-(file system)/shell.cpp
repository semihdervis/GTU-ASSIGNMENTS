#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

#include "file.h"
#include "directory.h"
#include "linkedFile.h"
#include "regularFile.h"
#include "shell.h"

using namespace std;

namespace OS {

Shell::Shell() {
    std::ifstream inFile("disk.txt");

    size = 0;

    root = new Directory("root");
    File* lfp = new LinkedFile(".", root);
    root->getFiles().push_back(lfp);

    current = root;

    deserializeDirectories(root, inFile);
}

void Shell::mkdir(std::string n, std::time_t tp) {
    File* linkedParentFile = new LinkedFile("..", current);
    File* dir = new Directory(n, tp);
    File* linkedThisFile = new LinkedFile(".", dir);
    
    auto& parentVec = current->getFiles();
    parentVec.push_back(dir);
    auto& thisVec = dynamic_cast<Directory*>(dir)->getFiles();

    thisVec.push_back(linkedParentFile);
    thisVec.push_back(linkedThisFile);

    ++(current->getCount());
}

void Shell::cd(std::string n) {
    for (const auto& it : *current) {
        if (it->getName() == n) {
            if (Directory* dp = dynamic_cast<Directory*>(it)) {
                current = dp;
                break;
            }
            if (LinkedFile* lfp = dynamic_cast<LinkedFile*>(it)) {
                if (Directory* dp = dynamic_cast<Directory*>(lfp->getFP())) {
                    current = dp;
                    break;
                }
            }
        }
    }
}

void Shell::rm(std::string n) {
    for (auto it = current->begin(); it != current->end(); ++it) {
        if ((*it)->getName() == n) {
            current->erase(it);
            break;
        }
    }
    --(current->getCount());
}

void Shell::ls() const {
    for (const auto& it : *current) {
        if (Directory* dp = dynamic_cast<Directory*>(it)) {
            cout << "D ";
        }
        else if (LinkedFile* lfp = dynamic_cast<LinkedFile*>(it)) {
            if (Directory* dp = dynamic_cast<Directory*>(lfp->getFP())) {
                cout << "D ";
            }
            else cout << "F ";
        }
        else cout << "F ";
        cout << it->getName() << "               ";
        if (LinkedFile* lfp = dynamic_cast<LinkedFile*>(it)) {
            if (Directory* dp = dynamic_cast<Directory*>(lfp->getFP())) {
                cout << dp->getTime();
            }
            else cout << it->getTime();
        }
        else cout << it->getTime();
        if (RegularFile* rfp = dynamic_cast<RegularFile*>(it)) {
            cout << "    " << rfp->getSize() << " Bytes";
        }
        cout << endl;
    }
}

void Shell::lsR(File* fil, int depth) const {
    if (Directory* dp = dynamic_cast<Directory*>(fil)) {
        for (const auto& it: *dp) {
            if (LinkedFile* lf = dynamic_cast<LinkedFile*>(it)) ;
            else {
                for (int i = 0; i < depth; ++i) {
                    cout << "   "; // Add indentation for better readability
                }
                cout << it->getName() << endl;
            }
            lsR(it, depth + 1);
        }
    }
}

void Shell::cp(std::string path) {
    std::ifstream inputFile(path); 

    if (!inputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return;
    }

    // Extract the file name
    size_t lastSlashPos = path.find_last_of('/');
    std::string fileName = path.substr(lastSlashPos + 1);

    File* rf = new RegularFile(fileName, inputFile);

    current->getFiles().push_back(rf);
    ++(current->getCount());
}

void Shell::cat(std::string n) const {
    for (const auto& it : *current) {
        if (it->getName() == n) {
            if (RegularFile* rfp = dynamic_cast<RegularFile*>(it)) {
                cout << rfp->getData() << endl;
                break;
            }
            if (LinkedFile* lfp = dynamic_cast<LinkedFile*>(it)) {
                if (RegularFile* rfp = dynamic_cast<RegularFile*>(lfp->getFP())) {
                    cout << rfp->getData() << endl;
                    break;
                }
            }
        }
    }
}

void Shell::touch(std::string n, const std::string& data, std::time_t tp) {
    // create a regular file
    File* rfp = new RegularFile(n, data, tp);
    current->getFiles().push_back(rfp);
    ++(current->getCount());
}

void Shell::link(const std::string& target, const std::string& linkName) {
    for (const auto& it : *current) {
        if (it->getName() == target) {
            File* lfp = new LinkedFile(linkName, it);
            current->getFiles().push_back(lfp);
        }
    }
}

Directory& Shell::getRoot() {
    return *root;
}

Directory& Shell::getCurrent() {
    return *current;
}

int Shell::getSize() const {return size;}

void Shell::serializeDirectoriesToFile(Directory* dir, std::ofstream& outFile) {
    outFile << "D" << " ";
    outFile << dir->getCount() << " ";
    outFile << dir->getName() << " ";
    outFile << dir->getT() << endl;

    for (const auto& it : *dir) {
        if (Directory* dp = dynamic_cast<Directory*>(it)) {
            serializeDirectoriesToFile(dp, outFile);
        } else if (RegularFile* rfp = dynamic_cast<RegularFile*>(it)) {
            outFile << "R" << " ";
            outFile << rfp->getName() << " ";
            outFile << rfp->getT() << endl;
            outFile << rfp->getData() << endl;
            outFile << "STOP" << endl;
        }
    }
}

void Shell::deserializeDirectories(Directory* dir, std::ifstream& inFile) {
    string type;
    if (!(inFile >> type)) return;
    if (type == "D") {
        int num;
        inFile >> num;
        string name;
        inFile >> name;
        int date;
        inFile >> date;
        mkdir(name, date);
        cd(name);
        if (name == "root") {
            rm("..");
            root = current;
            ++(root->getCount());
        }
        for (int i = 0; i < num; i++) {
            deserializeDirectories(current, inFile);
        }
        cd("..");
        size += 100;
    }
    else if (type == "R") {
        string name;
        inFile >> name;
        int date;
        inFile >> date;
        string data;
        std::string line;
        std::getline(inFile, line);
        while (std::getline(inFile, line) && line != "STOP") {
            data += line;
            data += "\n";
        }
        data.pop_back();
        touch(name, data, date);
        size += data.size();
    }
}

Shell::~Shell() {
    //delete root;
}

}