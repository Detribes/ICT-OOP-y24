#include "MemoryStorage.h"

#include <streambuf>
#include <istream>

MemoryStorage::MemoryStorage(std::filesystem::path path) : path_(std::move(path))
{
}

// путь к изначальному месту хранения
std::filesystem::path MemoryStorage::getPath() {
    return path_;
}

// записывает данные в оригинальный файл
bool MemoryStorage::restoreData() {
    return true;
}

// сохраняет данные из файла
bool MemoryStorage::updateData(std::vector<uint8_t> data) {
    return true;
}