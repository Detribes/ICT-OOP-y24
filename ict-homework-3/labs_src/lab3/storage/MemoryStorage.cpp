#include "MemoryStorage.h"

MemoryStorage::MemoryStorage(std::string name,std::vector <char> data) {
    for(char dt: data){
        this->data_.push_back(dt);
    }
    this->name_=name;
}

std::string MemoryStorage::getName() {
    return name_;
}

std::ofstream MemoryStorage::copyInto() {
    std::ofstream outputStream(name_,std::ios::binary);
    size_t file_size =  std::filesystem::file_size(name_);
    data_.resize(file_size/sizeof(std::byte));
    std::iota(data_.begin(), data_.end(), 0);
    std::random_shuffle(data_.begin(), data_.end());
    outputStream.write((char*)&data_[0], file_size);
    outputStream.close();
    return outputStream;
}
std::ifstream MemoryStorage::retrieve() {
    std::ifstream inputStream(name_, std::ios::binary);
    size_t file_size =  std::filesystem::file_size(name_);
    inputStream.seekg(0, std::ios::beg);
    inputStream.read(data_.data(), file_size);
    inputStream.close();
    return inputStream;
}
