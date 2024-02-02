#ifndef REGULARFILE_H
#define REGULARFILE_H

#include <iostream>
#include <fstream>
#include <string>

#include "file.h"

namespace OS {

using namespace std;

class RegularFile : public File {
public:
    RegularFile(string n, ifstream& inputFile, std::time_t tp = std::time(0)) : File(n, tp) {
        data = string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    }
    RegularFile(string n, const string& d, std::time_t tp = std::time(0)) : File(n, tp), data(d) {}
    int getSize() { return data.size(); }
    const string& getData() const {return data;}
private:
    string data;
};

}

#endif //REGULARFILE_H