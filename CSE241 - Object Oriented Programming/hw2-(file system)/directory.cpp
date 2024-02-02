#include "Directory.h"

namespace OS {

Directory::Directory(std::string n, std::time_t tp) : File(n, tp), count(0) {}

std::vector<File*>& Directory::getFiles() {
    return files;
}

Directory::iterator::iterator(std::vector<File*>::iterator it) : current(it) {}

File*& Directory::iterator::operator*() {
    return *current;
}

Directory::iterator& Directory::iterator::operator++() {
    ++current;
    return *this;
}

bool Directory::iterator::operator!=(const iterator& other) const {
    return current != other.current;
}

Directory::iterator Directory::erase(iterator& it) {
    return iterator(files.erase(it.getCurrent()));
}

Directory::iterator Directory::begin() {
    return iterator(files.begin());
}

Directory::iterator Directory::end() {
    return iterator(files.end());
}

int& Directory::getCount() {
    return count;
}

Directory::~Directory() {
    for (auto& it : files) {
        delete it;
    }
    delete this;
}

}