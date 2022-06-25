#include "MockRepository.h"
#include "../util/factory/RestorePointFactory.h"

MockRepository::MockRepository(std::string name, RestorePointType type) : name_(std::move(name)), path_("."), type_(type) {
    load();
}

std::string MockRepository::getName() {
    return name_;
}

void MockRepository::addRestorePoint(std::string name, std::shared_ptr<IRestorePoint> restorePoint) {
    restorePoints_.insert(std::make_pair(name, restorePoint));
}

std::shared_ptr<IRestorePoint> MockRepository::getRestorePoint(std::string name) {
    if (restorePoints_.count(name) == 0)
        throw std::invalid_argument("Restore point '" + name + "' doesn't exist'");

    return restorePoints_.at(name);
}

RestorePointType MockRepository::getRestorePointType() {
    return type_;
}

std::filesystem::path MockRepository::getLocation() {
    return path_;
}

void MockRepository::load() {
}

std::unordered_map<std::string, std::shared_ptr<IRestorePoint>> MockRepository::getRestorePoints() {
    return restorePoints_;
}

void MockRepository::restore(std::string name) {
    for (auto s : getRestorePoint(name)->getStorages())
        s.second->restoreData();
}