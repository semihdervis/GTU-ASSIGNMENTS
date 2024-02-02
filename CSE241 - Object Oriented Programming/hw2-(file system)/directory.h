#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <vector>
#include "file.h"

namespace OS {

class Directory : public File {
public:
    Directory(std::string n, std::time_t tp = std::time(0));

    std::vector<File*>& getFiles();

    class iterator {
    public:
        iterator(std::vector<File*>::iterator it);

        File*& operator*();
        iterator& operator++();
        bool operator!=(const iterator& other) const;
        std::vector<File*>::iterator& getCurrent() {return current;}
    private:
        std::vector<File*>::iterator current;
    };

    iterator erase(iterator& it);
    iterator begin();
    iterator end();

    int& getCount();

    virtual ~Directory() override;

private:
    int count;
    std::vector<File*> files;
};

}

#endif //DIRECTORY_H
