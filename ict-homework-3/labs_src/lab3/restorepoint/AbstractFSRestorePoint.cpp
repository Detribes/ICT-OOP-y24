#include "AbstractFSRestorePoint.h"

AbstractFSRestorePoint::AbstractFSRestorePoint(std::string name, std::filesystem::path path)  : AbstractRestorePoint(name){
    this->path_ = path.append(name);
}

std::filesystem::path AbstractFSRestorePoint::getPath() {
    return path_;
}