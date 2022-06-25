#ifndef ICT_HOMEWORK_3_IREPOSITORY_H
#define ICT_HOMEWORK_3_IREPOSITORY_H

#include <string>
#include "../restorepoint/IRestorePoint.h"
#include "../util/factory/enums/RestorePointType.h"
#include "../util/factory/enums/RepositoryType.h"

class IRepository {
public:
    IRepository() = default;

    virtual std::string getName() = 0;
    virtual void addRestorePoint(std::string name, std::shared_ptr<IRestorePoint> restorePoint) = 0;
    virtual std::shared_ptr<IRestorePoint> getRestorePoint(std::string name) = 0;
    virtual std::unordered_map<std::string, std::shared_ptr<IRestorePoint>> getRestorePoints() = 0;
    virtual std::filesystem::path getLocation() = 0;
    virtual RestorePointType getRestorePointType() = 0;
    virtual RepositoryType getRepositoryType() = 0;
    // загружает RestorePoints и Storage откуда-либо (зависит от имплементации)
    virtual void load() = 0;
    // восстанавливает файлы из RestorePoint с указанным именем 
    virtual void restore(std::string name) = 0;

    ~IRepository() = default;
};
#endif //ICT_HOMEWORK_3_IREPOSITORY_H
