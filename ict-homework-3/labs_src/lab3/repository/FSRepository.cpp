#include "FSRepository.h"
#include "../util/factory/RestorePointFactory.h"

FSRepository::FSRepository(std::string name, std::filesystem::path path, RestorePointType type) : name_(std::move(name)), path_(path), type_(type) {
    if (!std::filesystem::exists(path))
        throw std::invalid_argument("Path '" + path.string() + "' does not exist.");
    if (!std::filesystem::is_directory(path))
        throw std::invalid_argument("Path '" + path.string() + "' is not a directory.");
}

std::string FSRepository::getName() {
    return name_;
}

void FSRepository::addRestorePoint(std::string name, std::shared_ptr<IRestorePoint> restorePoint) {
    restorePoints_.insert(std::make_pair(name, restorePoint));
}

std::shared_ptr<IRestorePoint> FSRepository::getRestorePoint(std::string name) {
    if (restorePoints_.count(name) == 0)
        throw std::invalid_argument("Restore point '" + name + "' doesn't exist'");

    return restorePoints_.at(name);
}

RestorePointType FSRepository::getRestorePointType() {
    return type_;
}

std::filesystem::path FSRepository::getLocation() {
    return path_;
}

std::unordered_map<std::string, std::shared_ptr<IRestorePoint>> FSRepository::getRestorePoints() {
    return restorePoints_;
}

void FSRepository::load() {
    try {
        for (auto &s : getRestorePoints()) {
            s.second->load();
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

void FSRepository::restore(std::string name) {
    // пересоздаём корневой каталог
    if (!std::filesystem::exists(path_)) {
        try {
            std::filesystem::create_directory(path_);
        } catch (const std::filesystem::filesystem_error &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    // ресторим содержимое
    for (auto &s : getRestorePoint(name)->getStorages()) {
        s.second->restoreData();
    }
}