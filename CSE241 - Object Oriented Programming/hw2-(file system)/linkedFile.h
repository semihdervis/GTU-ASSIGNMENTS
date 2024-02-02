#ifndef LINKEDFILE_H
#define LINKEDFILE_H

#include <iostream>
#include <string>

#include "file.h"

namespace OS {

class LinkedFile : public File {
public:
    LinkedFile(std::string n, File* f, std::time_t tp = std::time(0)) : File(n, tp), file(f) {}
    std::string getName() const override {
        return name;
    }
    File* getFP() {return file;}
private:
    File* file;
};

}

#endif //LINKEDFILE_H