#include "FileStorage.h"


FileStorage::FileStorage(std::filesystem::path path) : path_(std::move(path))
{
}

// путь к изначальному месту хранения
std::filesystem::path FileStorage::getPath() {
    return path_;
}

// записывает данные в оригинальный файл
bool FileStorage::restoreData() {
    std::ofstream ofs(path_, std::ios::out | std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(data_.data()), data_.size());
    ofs.close();
    return true;
}

// сохраняет данные из файла
bool FileStorage::updateData(std::vector<uint8_t> data) {
    data_ = std::vector<uint8_t>(data);
    return true;
}