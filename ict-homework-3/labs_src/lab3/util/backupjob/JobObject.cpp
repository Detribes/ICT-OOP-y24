#include "JobObject.h"

JobObject::JobObject(IStorage storage) {
    this->storage_ = storage;
}

IStorage JobObject::getStorage() {
    return storage_;
}