#include "MockJobObject.h"

MockJobObject::MockJobObject(std::string fileName, std::vector<uint8_t> data) : fileName_(std::move(fileName)), data_(data)
{
}

std::filesystem::path MockJobObject::getFullPath() {
    return std::filesystem::path(fileName_);
}

std::vector<uint8_t> MockJobObject::getContents() {
    return data_;
}