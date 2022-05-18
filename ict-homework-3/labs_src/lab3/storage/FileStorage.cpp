#include "FileStorage.h"


FileStorage::FileStorage(std::string name,std::string path){
    this->path_=path;
    this->name_=name;
};

std::filesystem::path FileStorage::getPath() {return path_;}

std::string FileStorage::getName() {
    return name_;
}

std::ofstream FileStorage::copyInto() {
    std::filesystem::path parent = path_.parent_path();
    if (!std::filesystem::exists(parent)){
        try{
            std::filesystem::create_directory(parent);
        } catch (const std::filesystem::filesystem_error& e){
            std::cerr<<e.what()<<std::endl;
        }
    }

    std::ofstream outputStream;

    if(!std::filesystem::exists(path_)){
       std::ofstream outputStream (path_, std::ios::binary);
       size_t fileSize = std::filesystem::file_size(path_);
       outputStream.write(reinterpret_cast<const char *>(&fileSize), sizeof(fileSize));
    } else {
        outputStream.open(path_, std::ios::binary);
        size_t fileSize = std::filesystem::file_size(path_);
        outputStream.write(reinterpret_cast<const char *>(&fileSize), sizeof(fileSize));
    }
return outputStream;
}
std::ifstream FileStorage::retrieve() {

    std::ifstream inputStream;
    if (!std::filesystem::exists(path_)){
        std::ifstream inputStream (path_, std::ios::binary);
        size_t fileSize = std::filesystem::file_size(path_);
        while(inputStream.read(reinterpret_cast<char *>(&fileSize), sizeof(fileSize))){}
    }
    else{
        inputStream.open(path_, std::ios::binary);
        size_t fileSize = std::filesystem::file_size(path_);
        while(inputStream.read(reinterpret_cast<char *>(&fileSize), sizeof(fileSize))){}
    }

    try{
        if(!inputStream){
            throw std::fstream::failure("File open exception");
        }
        inputStream.open(path_);
    }
    catch(std::fstream::failure& e){
        std::cerr<<e.what()<<std::endl;
    }
    return inputStream;
}