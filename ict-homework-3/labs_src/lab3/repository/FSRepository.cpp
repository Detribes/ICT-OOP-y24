#include "FSRepository.h"
#include "../util/factory/RestorePointFactory.h"

FSRepository::FSRepository(std::string name, std::filesystem::path path, RestorePointType type) {
    if(!std::filesystem::is_directory(path)){
        throw new std::invalid_argument("Path '" + path.string() + "' is not a directory.");
    }
    this->name_ = name;
    this->path_ = path;
    this->type_ = type;
    load();
}

std::string FSRepository::getName() {
    return name_;
}

void FSRepository::addRestorePoint(std::string name, IRestorePoint restorePoint) {
    restorePoints_.insert(std::make_pair(name, restorePoint));
}

IRestorePoint FSRepository::getRestorePoint(std::string name) {
    if(restorePoints_.count(name) == 0){
        throw new std::invalid_argument("Restore point '" + name + "' doesn't exist'");
    }
    return restorePoints_.at(name);
}

RestorePointType FSRepository::getRestorePointType() {
    return type_;
}

std::filesystem::path FSRepository::getPath() {
    return path_;
}

std::string FSRepository::getLocation() {
    return path_.string();
}

void FSRepository::load() {
    try {
        std::vector<std::filesystem::path> dir;
        for (std::filesystem::path dirFile: std::filesystem::directory_iterator{getPath()}) {
            if (is_regular_file(dirFile)) {
                dir.push_back(dirFile);
            }
        }
        dir.erase(dir.begin());
        for (std::filesystem::path p: dir){
            std::string restorePointName = p.filename().string();
            IRestorePoint restorePoint = RestorePointFactory::create((const IRepository &) *this,
                                                                     getRestorePointType(),
                                                                     restorePointName);
            restorePoint.load();
            addRestorePoint(restorePointName, restorePoint);
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

std::unordered_map<std::string, IRestorePoint> FSRepository::getRestorePoints() {
    return restorePoints_;
}