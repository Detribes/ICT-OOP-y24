#ifndef ICT_HOMEWORK_3_ISTORAGE_H
#define ICT_HOMEWORK_3_ISTORAGE_H

#include <fstream>
#include <iostream>
#include <string>
#include <exception>
#include <numeric>
#include <vector>
#include <filesystem>


class IStorage{
public:
    IStorage(){}
    virtual ~IStorage(){}
    virtual std::string getName();
    virtual std::ifstream retrieve();
    virtual std::ofstream copyInto();

};
#endif //ICT_HOMEWORK_3_ISTORAGE_H
