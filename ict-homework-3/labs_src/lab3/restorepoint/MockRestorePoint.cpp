#include "MockRestorePoint.h"

MockRestorePoint::MockRestorePoint(std::string name)  : AbstractRestorePoint(name)
{
}

void MockRestorePoint::save() {
    for (auto &r : getStorages()) {
        std::cout << "Saved " << r.first << std::endl;
    }
}

void MockRestorePoint::load() {
    for (auto &r : getStorages()) {
        std::cout << "Loaded " << r.first << std::endl;
    }
}