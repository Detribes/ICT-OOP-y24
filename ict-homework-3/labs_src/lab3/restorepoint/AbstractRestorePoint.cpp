#include "AbstractRestorePoint.h"

AbstractRestorePoint::AbstractRestorePoint(std::string name) {
    this->name_=name;
}

std::string AbstractRestorePoint::getName() {
    return name_;
}

IStorage AbstractRestorePoint::getStorage(std::string name) {
    return actualStorages_.at(name);

}

std::unordered_map<std::string, IStorage> AbstractRestorePoint::getStorages() {
    return actualStorages_;
}

void AbstractRestorePoint::addNewStorage(std::string name, IStorage storage) {
    storagesToCopy_.insert(std::make_pair(name, storage));
}

void AbstractRestorePoint::resetStoragesToCopy() {
    storagesToCopy_.clear();
}

std::unordered_map<std::string, IStorage> AbstractRestorePoint::getStoragesToCopy() {
    return storagesToCopy_;
}