#include "FileJobObject.h"

#include <fstream>

FileJobObject::FileJobObject(std::filesystem::path fullQualifiedPath) : fullQualifiedPath_(fullQualifiedPath)
{
}

std::filesystem::path FileJobObject::getFullPath() {
    return fullQualifiedPath_;
}

std::vector<uint8_t> FileJobObject::getContents() {
    std::ifstream stream(fullQualifiedPath_, std::ios::in | std::ios::binary);
    std::vector<uint8_t> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());

    return contents;
}