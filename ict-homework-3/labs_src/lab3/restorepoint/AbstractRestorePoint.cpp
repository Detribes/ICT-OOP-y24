#include "AbstractRestorePoint.h"

#include "../util/factory/StorageFactory.h"

AbstractRestorePoint::AbstractRestorePoint(std::string name) : name_(std::move(name)) 
{
}

std::string AbstractRestorePoint::getName() {
    return name_;
}

std::shared_ptr<IStorage> AbstractRestorePoint::getStorage(std::string name) {
    return actualStorages_.at(name);
}

std::unordered_map<std::string, std::shared_ptr<IStorage>> AbstractRestorePoint::getStorages() {
    return actualStorages_;
}

void AbstractRestorePoint::addNewStorage(std::string name, std::shared_ptr<IStorage> storage) {
    actualStorages_.insert(std::make_pair(name, storage));
}

void AbstractRestorePoint::generate(std::list<std::shared_ptr<IJobObject>> jobs) {
    for (auto job : jobs) {
        std::shared_ptr<IStorage> newStor = StorageFactory::create(
            StorageType::MEMORY,
            job->getFullPath().replace_filename(job->getFullPath().filename().string() + "_" + name_)
        );
        
        // Запихиваем данные в сторадж
        newStor->updateData(job->getContents());
        addNewStorage(job->getFullPath(), newStor);
    }
}