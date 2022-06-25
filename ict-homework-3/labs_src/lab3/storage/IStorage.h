#ifndef ICT_HOMEWORK_3_ISTORAGE_H
#define ICT_HOMEWORK_3_ISTORAGE_H

#include <fstream>
#include <iostream>
#include <string>
#include <exception>
#include <numeric>
#include <vector>
#include <filesystem>

class IStorage {
public:
    IStorage() = default;
    
    // путь к изначальному месту хранения
    virtual std::filesystem::path getPath() = 0;
    // записывает данные в оригинальный файл
    virtual bool restoreData() = 0;
    // сохраняет данные из файла
    virtual bool updateData(std::vector<uint8_t>) = 0;

    ~IStorage() = default;
};
#endif //ICT_HOMEWORK_3_ISTORAGE_H
