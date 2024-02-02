#ifndef SHELL_H
#define SHELL_H

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

namespace OS {

class Shell {
public:
    Shell();

    void mkdir(std::string n, std::time_t tp = std::time(0));
    void cd(std::string n);
    void rm(std::string n);
    void ls() const;
    void lsR(File* fil, int depth = 0) const;
    void cp(std::string path);
    void cat(std::string n) const;
    void touch(std::string n, const std::string& data, std::time_t tp = std::time(0));
    void link(const std::string& target, const std::string& linkName);

    Directory& getRoot();
    Directory& getCurrent();
    int getSize() const;

    void serializeDirectoriesToFile(Directory* dir, std::ofstream& outFile);
    void deserializeDirectories(Directory* dir, std::ifstream& inFile);

    virtual ~Shell();

private:
    Directory* root;
    Directory* current;
    int size;
};

}

#endif // SHELL_H
