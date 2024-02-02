#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>

namespace OS {

class File {
public:
    File(std::string n, std::time_t tp = std::time(0)) : name(n), t(tp) {}
    virtual std::string getName() const {return name;}
        std::string getTime() {
            char buffer[80];
            std::strftime(buffer, sizeof(buffer), "%b %d %H:%M", std::localtime(&t));
            std::string str = buffer;
            return str;
        }
    int getT() {return t;}
    virtual ~File() {};
protected:
    std::string name;
    std::time_t t;
};

}

#endif //FILE_H